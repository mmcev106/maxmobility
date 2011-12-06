
#include <QtGui>
#include <QtWebKit/QtWebKit>

#include "mainscreen.h"
#include "ui_mainscreen.h"
#include <QStringBuilder>
#include <QDateTime>
#include <phonon/VideoWidget>
#include <phonon/MediaObject>
#include <QBitmap>
#include <QPainter>
#include "preferences.h"
#include <QDir>
#include "upperboardevent.h"
#include "changespeedstep.h"
#include "changegradestep.h"
#include "waitstep.h"
#include "endstep.h"
#include "utils.h"
#include "time.h"
#include "screens.h"
#include "scorewidget.h"
#include "historyscreen.h"

static int HISTORY_HEIGHT = 13;

#ifdef Q_WS_MAC //used for testing on Mac's where the current directory defaults to inside the application folder
    static QString RUNNING_DUDE_IMAGE_PATH ="../../../images/Running Dude";
#else
    static QString RUNNING_DUDE_IMAGE_PATH ="images/Running Dude";
#endif

static bool _update = false;
static bool wheelchairDude=false;

static float TRACK_LENGTH = .25; // in miles

static int MAX_HEART_RATE = 220;


/********************************************
  *
  *        Audio Feedback Variables
  *
  *******************************************/
float spd_array[8];
float grd_array[8];

static int counter=0;       // used for counting minutes for periodic feedback
static float last_speed = 0;      // used for detecting speed change
static float last_grade = 0;      // used for detecting grade change
static bool change = false;

static bool playing_feedback = false;

/********************************************
  *
  *        End Audio Feedback Variables
  *
  *******************************************/

static float speed_offset = 0.0f;
static float grade_offset = 0.0f;

static float step_current_grade;
static float step_current_speed;

void zero(int array[], int length){

    for(int i=0;i<length;i++){
        array[i] = 0;
    }
}

static bool grade_stage;

static const int PERIODIC_UPDATE_DELAY = 2*60*1000;     // delay in ms between periodic updates
static const int HEART_RATE_DELAY   = 15*1000;       // delay in ms between checking the heartrate for HR control profile
static const int DETECT_CHANGE_DELAY = 250;          // delay in ms between checking speed and grade for change
static const int UPDATE_DISPLAY_DELAY = 100;
static const double HOURS_PER_UPDATE = ((double)UPDATE_DISPLAY_DELAY)/MILLIS_PER_HOUR;
//QTime LAST_UPDATE=currentTime();

MainScreen::MainScreen(QWidget *parent) :
    AbstractScreen(parent)
    ,ui(new Ui::MainScreen)
    ,secondTimer(new QTimer(this))
    ,feedbackTimer(new QTimer(this))
    ,detectChangeTimer(new QTimer(this))
    ,HRMTimer(new QTimer(this))
    ,hideScreenTimer(new QTimer(this))
    ,milliSecondTimer(new QTimer(this))
    ,playTimer(new QTimer(this))
    ,startTime(0)
    ,centerSize(756, 564)
    ,centerWidget(this)
    ,trackWidget(new QLabel(&centerWidget))
    ,runningDudeWidget(new QLabel(&centerWidget))
    ,speedHistoryWidget(this, speedHistory, HISTORY_LENGTH, HISTORY_HEIGHT, CIRCLE_BRICK_URL, HIGHLIGHTED_CIRCLE_BRICK_URL)
    ,gradeHistoryWidget(this, gradeHistory, HISTORY_LENGTH, HISTORY_HEIGHT, CIRCLE_BRICK_URL, HIGHLIGHTED_CIRCLE_BRICK_URL)
    ,player(new Phonon::VideoPlayer(Phonon::VideoCategory, this))
    ,audioSettingsWidget(NULL)
    ,tranquilSelectionWidget(NULL)
    ,trailSelectionWidget(NULL)
    ,scoreWidget(&centerWidget)
    ,videoMask(":/images/images/main_screen_large_video_mask.png")
    ,wheelchairDudeOn(":/images/images/Wheelchair Mode - (Active).png")
    ,wheelchairDudeOff(":/images/images/Wheelchair Mode - (Not Active).png")
    ,nextWorkoutStepIndex(0)
    ,nextWorkoutStepTime(0)
    ,distance(0)
    ,speed(0)
    ,grade(0)
    ,heartRate(0)
    ,weight(0)
    ,recordingWorkout(FALSE)
    ,lastStepRecordedTime(0)
    ,pauseTime(0)
//    ,safetyMessageScreen(NULL, "Replace safety magnet.\n\nPress the Start Button to continue.")
    ,webview(new WebWidget(HOME_URL))
{
    ui->setupUi(this);
    setAttribute( Qt::WA_DeleteOnClose, false );

    //Put the background behind the player
    ui->backgroundLabel->lower();

    connect(secondTimer, SIGNAL(timeout()), this, SLOT( updateDisplay()));
    secondTimer->setSingleShot(false);
    secondTimer->setInterval(UPDATE_DISPLAY_DELAY);

    connect(feedbackTimer,SIGNAL(timeout()), this, SLOT( periodicFeedback()));
    feedbackTimer->setSingleShot(false);
    feedbackTimer->setInterval(PERIODIC_UPDATE_DELAY);  // every 2 minutes

    connect(HRMTimer,SIGNAL(timeout()),this,SLOT(CheckHeartRate()));
    HRMTimer->setSingleShot(false);
    HRMTimer->setInterval(HEART_RATE_DELAY);

    connect(detectChangeTimer,SIGNAL(timeout()), this, SLOT(detectChangeFeedback()));
    detectChangeTimer->setSingleShot(false);
    detectChangeTimer->setInterval(DETECT_CHANGE_DELAY);

    connect(milliSecondTimer, SIGNAL(timeout()), this, SLOT( updateRunningDudeImage()));
    milliSecondTimer->setSingleShot(false);
    milliSecondTimer->setInterval(10);

    connect(hideScreenTimer, SIGNAL(timeout()), this, SLOT( hide()));
    hideScreenTimer->setSingleShot(true);
    hideScreenTimer->setInterval(5000);

    connect(Utils::realTimeFeedback, SIGNAL(finished()),this,SLOT(feedbackEnded()));

    //     add the history widgets
    int historyY = 577;
    gradeHistoryWidget.move(27,historyY);
    speedHistoryWidget.move(930,historyY);

    QPoint centerPosition(133, 101);

    QPixmap trackBitmap(RUNNING_DUDE_IMAGE_PATH + "/Track_Background.png");

    centerWidget.move(centerPosition);
    centerWidget.setFixedSize(centerSize);
    centerWidget.setMask(videoMask.mask());

    player->videoWidget()->setParent(&centerWidget);
    player->setFixedSize(centerSize);
    player->videoWidget()->setFixedSize(centerSize);
    player->videoWidget()->hide();
    connect(player, SIGNAL(finished()), this, SLOT(restartVideo()));

    tranquilSelectionWidget.setParent(&centerWidget);
    tranquilSelectionWidget.setVisible(false);

    trailSelectionWidget.setParent(&centerWidget);
    trailSelectionWidget.setVisible(false);

    audioSettingsWidget.setParent(this);
    audioSettingsWidget.move(centerPosition);
    audioSettingsWidget.setFixedSize(centerSize);
    audioSettingsWidget.setVisible(false);

    scoreWidget.setVisible(false);

    trackWidget->setFixedSize(trackBitmap.size());
    /**
      * Since the track images are slightly smaller than the center widget,
      * move the trackWidget a bit so all four corners are (somewhat) rounded.
      */
    trackWidget->move(3,3);
    trackWidget->setPixmap(trackBitmap);
    trackWidget->show();

    runningDudeWidget->setFixedSize(centerSize);
    runningDudeWidget->show();

    ui->wheelchairDudeImage->setParent(this);
    ui->wheelchairDudeImage->setVisible(true);
    ui->wheelchairDudeImage->raise();
    ui->wheelchairDude_invisibleButton->setParent(this);
    ui->wheelchairDude_invisibleButton->setVisible(true);
    ui->wheelchairDude_invisibleButton->raise();

    webview->setParent(&centerWidget);
    webview->hide();

    centerWidget.raise();
    audioSettingsWidget.raise();

    //    update the fields before the windows is initially displayed

    updateDisplay();
}

MainScreen* MainScreen::mainScreen = NULL;
Workout* MainScreen::workout = NULL;

void MainScreen::createMainScreen(QWidget* parent){
    mainScreen = new MainScreen(parent);
    mainScreen->hide();
}

MainScreen* MainScreen::getMainScreen(){
    return mainScreen;
}

Workout* MainScreen::getWorkout(){
    return workout;
}

void MainScreen::startWorkout(Workout* workout){
    startWorkout(workout, FALSE);
}

void MainScreen::defaultWorkout(){

    this->workout = Workout::createWorkout(QString("Manual"),Utils::getDEF_SPEED(),0,QUICK_WORKOUT_LENGTH);
    this->recordingWorkout = false;

    Utils::accFeedback->clear();

    // clear audio feedback variables
    for (int i=0;i<8;i++)
    {
        spd_array[i]=0.0f;
        grd_array[i]=0.0f;
    }
    counter=0;
    last_speed = 0.0f;
    last_grade = 0.0f;
    change = false;

    weight = workout->_weight;

    startTime = QDateTime::currentMSecsSinceEpoch();
    distance = 0;
    nextWorkoutStepIndex = 0;
    nextWorkoutStepTime = 0;
    calories=0;
    stage=0;
    lastPosition=0;

    if(Preferences::getMeasurementSystem()){
        ui->distanceMetricLabel->setText("mi");
        ui->paceMetricLabel->setText("(mins/mi)");
        ui->speedMetricLabel->setText("mph");
        if (!weight)
            weight=72.5;
        else
            weight=weight*.45359237;
    }
    else {
        ui->distanceMetricLabel->setText("km");
        ui->paceMetricLabel->setText("(mins/km)");
        ui->speedMetricLabel->setText("km/h");
        if (!weight)
            weight=72.5;
    }

    zero(speedHistory, HISTORY_LENGTH);
    zero(gradeHistory, HISTORY_LENGTH);

    secondTimer->start();
    milliSecondTimer->start();
    feedbackTimer->start();
    detectChangeTimer->start();

    speed_offset=0.0f;
    grade_offset=0.0f;
    step_current_speed = 0.0f;
    step_current_grade = 0.0f;

    updateDisplay();
}

void MainScreen::recordWorkout(Workout* workout){

    lastStepRecordedTime = QDateTime::currentMSecsSinceEpoch();

    startWorkout(workout, TRUE);
}

void MainScreen::startWorkout(Workout* workout, bool recordWorkout){
    // moved these to the beginning so that the state change would always happen before
    // the spd_diff and grd_diff got sent to the lower board (so that they would not
    // be ignored by the lower board).
    if(Preferences::isTestingMode()){
        Screens::show(this);
    }
    else{
        Preferences::setCurrentState(ON_OFF_MASK);
    }

    this->workout = workout;
    this->recordingWorkout = recordWorkout;

    Utils::accFeedback->clear();

    // clear audio feedback variables
    for (int i=0;i<8;i++)
    {
        spd_array[i]=0.0f;
        grd_array[i]=0.0f;
    }
    counter=0;
    last_speed = 0.0f;
    last_grade = 0.0f;
    change = false;

    speed_offset=0.0f;
    grade_offset=0.0f;
    step_current_speed = 0.0f;
    step_current_grade = 0.0f;

    weight = workout->_weight;

    startTime = QDateTime::currentMSecsSinceEpoch();
    distance = 0;
    nextWorkoutStepIndex = 0;
    nextWorkoutStepTime = 0;
    calories=0;
    stage=0;
    lastPosition=0;

    if(Preferences::getMeasurementSystem()){
        ui->distanceMetricLabel->setText("mi");
        ui->paceMetricLabel->setText("(mins/mi)");
        ui->speedMetricLabel->setText("mph");
        if (!weight)
            weight=72.5;
        else
            weight=weight*.45359237;
    }
    else {
        ui->distanceMetricLabel->setText("km");
        ui->paceMetricLabel->setText("(mins/km)");
        ui->speedMetricLabel->setText("km/h");
        if (!weight)
            weight=72.5;
    }

    zero(speedHistory, HISTORY_LENGTH);
    zero(gradeHistory, HISTORY_LENGTH);

    secondTimer->start();
    milliSecondTimer->start();
    feedbackTimer->start();
    detectChangeTimer->start();
//    qDebug() << "Workout name contains HR?" << workout->name.contains("Heart Rate");
//    if ( workout->name.contains("Heart Rate") )
        HRMTimer->start();
        grade_stage = true;     // has to be true so that when the first is called it becomes false

    wheelchairDude = false;
    ui->wheelchairDudeImage->setPixmap(wheelchairDudeOff);

    if (this->recordingWorkout)
    {
        QList<Step*>* steps = workout->steps;
        for( int i=nextWorkoutStepIndex;i<steps->length();i++)
        {
            Step* step = steps->at(nextWorkoutStepIndex);
            nextWorkoutStepIndex++;

            if(step->getType() == SPEED_CHANGE_TYPE)
            {
                ChangeSpeedStep* changeSpeedStep = (ChangeSpeedStep*) step;
                Preferences::setCurrentSpeed(changeSpeedStep->speed);
            }
            else if(step->getType() == GRADE_CHANGE_TYPE)
            {
                ChangeGradeStep* changeGradeStep = (ChangeGradeStep*) step;
                Preferences::setCurrentGrade(changeGradeStep->grade);
            }
        }
    }

    showWorkoutVisualization();
    updateDisplay();
}

void MainScreen::processNextWorkoutStep() {

    if(workout != NULL)
    {
        if (!this->recordingWorkout)
        {
            QList<Step*>* steps = workout->steps;
            for( int i=nextWorkoutStepIndex;i<steps->length();i++){
                Step* step = steps->at(nextWorkoutStepIndex);
                nextWorkoutStepIndex++;

                if(step->getType() == SPEED_CHANGE_TYPE){
                    ChangeSpeedStep* changeSpeedStep = (ChangeSpeedStep*) step;

                    step_current_speed = changeSpeedStep->speed;
                    Preferences::setCurrentSpeed(changeSpeedStep->speed + speed_offset);

    //                qDebug() << "Workout speed change: " << changeSpeedStep->speed;
                }
                else if(step->getType() == GRADE_CHANGE_TYPE){
                    ChangeGradeStep* changeGradeStep = (ChangeGradeStep*) step;
                    step_current_grade = changeGradeStep->grade;
                    Preferences::setCurrentGrade(changeGradeStep->grade + grade_offset);
//                    if ( workout->name.contains("Heart Rate") )
//                    {
                        grade_stage= !grade_stage;
//                    }

    //                qDebug() << "Workout grade change: " << changeGradeStep->grade;
                }
                else if(step->getType() == WAIT_TYPE){
                    WaitStep* waitStep = (WaitStep*) step;
                    nextWorkoutStepTime += waitStep->time;
    //                qDebug() << "Workout wait: " << waitStep->time;

                    /**
                      * Return.  This method will get called again during updateDisplay()
                      * and will pick up where it left off.
                      */
                    return;
                }

                else if(step->getType() == END_TYPE){
                    //This would show a screen in the center widget with time and stuff
                    // end type must be appended onto the end of the programs for this to be called

    //                EndStep* endStep = (EndStep*) step;
    //                nextWorkoutStepTime += endStep->time;
    //                QString first("You completed the program ");
    //                first.append(workout->name);
    //                QString second= QString("Time: %1:%2 \nDistance: %3.%4 \nCalories Burned: %5")
    //                                .arg(minutes,2,'g',-1,QLatin1Char('0')).arg(seconds,2,'g',-1,QLatin1Char('0'))
    //                                .arg(((int)distance)%100).arg(((int)(distance*100))%100,2,'g',-1,QLatin1Char('0')).arg((int)calories);
    //                ShowWidget(SCORE_VISUALIZATION, first, second);
                    return;
                }
            }

            // We've completed the workout steps, and we're not recording, so end the workout.
            Preferences::setCurrentState(0);

            if(Preferences::isTestingMode())
            {
                endWorkout();
            }
        }   // end if ! recording
    }
}

void MainScreen::writeHistoryEntry(){

    QFile historyFile(Preferences::getCurrentHistoryPath());
    historyFile.open(QFile::Append);

    QTextStream stream(&historyFile);

    QDateTime now = QDateTime::currentDateTime();

    stream << now.toString(HistoryScreen::DATE_FORMAT);
    stream << "\t";

    stream << workout->name;
    stream << "\t";

    long elapsedTimeMillis = QDateTime::currentMSecsSinceEpoch() - startTime;
    long seconds = elapsedTimeMillis/1000;

    stream << seconds;
    stream << "\t";

    stream << (int)calories;
    stream << "\t";

    stream << distance;
    stream << "\n";

    stream.flush();
    historyFile.close();
}

void MainScreen::recordWaitStep(){
    long currentTime = QDateTime::currentMSecsSinceEpoch();
    long waitTime = currentTime - lastStepRecordedTime;

    workout->steps->append(new WaitStep(waitTime));

    lastStepRecordedTime = currentTime;
}

void MainScreen::keyPressEvent(QKeyEvent* event){

    bool eventConsumed = FALSE;

    if(Preferences::isTestingMode()){
        if(recordingWorkout){
            if(event->key() == Qt::Key_G){
                eventConsumed = TRUE;
                recordGradeChange(1.1);
            }
            else if(event->key() == Qt::Key_S){
                eventConsumed = TRUE;
                recordSpeedChange(2.2);
            }
        }

        if(event->key() == Qt::Key_P){

            eventConsumed = TRUE;

            if(isWorkoutPaused()){
                unPauseWorkout();
            }
            else{
                pauseWorkout();
            }
        }
    }

    if(!eventConsumed){
        AbstractScreen::keyPressEvent(event);
    }
}

void MainScreen::pauseWorkout(){
    if(!isWorkoutPaused()){

        pauseTime = QDateTime::currentMSecsSinceEpoch();

        if(player->isPlaying()){
            player->pause();
        }
    }
}

void MainScreen::unPauseWorkout(){
    if(isWorkoutPaused()){

        long pauseLength = QDateTime::currentMSecsSinceEpoch() - pauseTime;
        startTime += pauseLength;
        pauseTime = 0;

        if(player->isPaused()){
            player->play();
        }
    }
}

bool MainScreen::isWorkoutPaused(){
    return pauseTime != 0;
}

void MainScreen::recordSpeedChange(float speed){
    recordWaitStep();
    workout->steps->append(new ChangeSpeedStep(speed));
}

void MainScreen::recordGradeChange(float grade){
    recordWaitStep();
    workout->steps->append(new ChangeGradeStep(grade));
}

void MainScreen::endWorkout(){

    qDebug() << "endWorkout()";

    QString message;
    if (workout && (workout->name.contains("Fire Fighter") || workout->name.contains("Fitness")) )
    {
         message = QString("%1 Test Results:\n\nYou Made It To Stage %2!").arg(workout->name).arg(stage);
         if (workout->name.contains("Fitness") && Preferences::getAverageHeartRate())
         {
             double VO2;
             if (Preferences::gender) // men
             {
                 switch(stage){
                    case 1: VO2=14.9; break;
                    case 2: VO2=19.6; break;
                    case 3: VO2=24.4; break;
                    case 4: VO2=29.2; break;
                    case 5: VO2=33.9; break;
                    default: VO2=0; break;
                    }
                 VO2=(VO2*(MAX_HEART_RATE-Preferences::getAge()-73))/(Preferences::getAverageHeartRate()-73);
             }
             else // women
             {
                 switch(stage){
                    case 1: VO2=14.9; break;
                    case 2: VO2=18.4; break;
                    case 3: VO2=22.0; break;
                    case 4: VO2=25.6; break;
                    case 5: VO2=29.2; break;
                    default: VO2=0; break;
                    }
                 VO2=(VO2*(MAX_HEART_RATE-Preferences::getAge()-63))/(Preferences::getAverageHeartRate()-63);
             }
             QString VO = QString("\nVO2 Max: %1").arg(VO2);
             message.append(VO);
         }

    }
    else{
        if (Preferences::getMeasurementSystem()==STANDARD)
        {
            message = QString("Workout Results: \n\nTime: %1:%2 \nDistance: %3.%4 mi \nCalories Burned: %5")
                          .arg(minutes,2,'g',-1,QLatin1Char('0')).arg(seconds,2,'g',-1,QLatin1Char('0'))
                          .arg(((int)distance)%100).arg(((int)(distance*100))%100,2,'g',-1,QLatin1Char('0')).arg((int)calories);
        }
        else
        {
            message = QString("Workout Results: \n\nTime: %1:%2 \nDistance: %3.%4 km \nCalories Burned: %5")
                          .arg(minutes,2,'g',-1,QLatin1Char('0')).arg(seconds,2,'g',-1,QLatin1Char('0'))
                          .arg(((int)distance)%100).arg(((int)(distance*100))%100,2,'g',-1,QLatin1Char('0')).arg((int)calories);
        }
    }

    hideWidgets();
    scoreWidget.setText(message, "");
    scoreWidget.setVisible(true);
    hideScreenTimer->start();

    Utils::realTimeFeedback->clear();

    if(Preferences::isUsbDrivePresent()){
        writeHistoryEntry();

        if(recordingWorkout){
            recordWaitStep();
            workout->save();
        }
    }

    delete workout;
    this->workout = NULL;   // needed for the test of !MainScreen::getWorkout()!!!!!!
    recordingWorkout = false;
    webview->SetUrl(HOME_URL);

    Preferences::accessibilityMode = false;

    secondTimer->stop();
    milliSecondTimer->stop();
    feedbackTimer->stop();
    detectChangeTimer->stop();
    HRMTimer->stop();

    step_current_speed = 0.0f;
    step_current_grade = 0.0f;
    speed_offset=0.0f;
    grade_offset=0.0f;
}

MainScreen::~MainScreen()
{
    hideWidgets();
    delete ui;

    player->stop();
    delete player;
    delete secondTimer;
    delete webview;
    delete workout;
}

void MainScreen::restartVideo(){

    player->stop();
    player->play();
}

void MainScreen::feedbackAppendNumber(int number,QList<QUrl> *lst)
{
    if (number < 100)
    {
        if (number < 21)
        {
            lst->append(QUrl(AUDIO_ROOT_DIR + QString("%1").arg(number) + ".wav"));
        }
        else
        {
            lst->append(QUrl(AUDIO_ROOT_DIR + QString("%1").arg(number - number%10) + ".wav"));
            if (number%10)
                lst->append(QUrl(AUDIO_ROOT_DIR + QString("%1").arg(number%10) + ".wav"));
        }
    }
    else
    {
        lst->append(QUrl(AUDIO_ROOT_DIR + QString("%1").arg(number/100) + ".wav"));
        lst->append(QUrl(AUDIO_ROOT_DIR + "hundred.wav"));
        number = number%100;
        if (number < 21)
        {
            lst->append(QUrl(AUDIO_ROOT_DIR + QString("%1").arg(number) + ".wav"));
        }
        else
        {
            lst->append(QUrl(AUDIO_ROOT_DIR + QString("%1").arg(number - number%10) + ".wav"));
            if (number%10)
                lst->append(QUrl(AUDIO_ROOT_DIR + QString("%1").arg(number%10) + ".wav"));
        }
    }
}


void MainScreen::feedbackAppendNumber(float number,QList<QUrl> *lst)
{
    double intpartD;
    double fracpart = modf(number,&intpartD);
    if (fracpart>0.0f && fracpart < 0.1)
        fracpart = 0.1;

    int intpart = (int)intpartD;

    if (intpart < 100)
    {
        if (intpart < 21)
        {
            lst->append(QUrl(AUDIO_ROOT_DIR + QString("%1").arg(intpart) + ".wav"));
        }
        else
        {
            lst->append(QUrl(AUDIO_ROOT_DIR + QString("%1").arg(intpart - intpart%10) + ".wav"));
            if (intpart%10)
                lst->append(QUrl(AUDIO_ROOT_DIR + QString("%1").arg(intpart%10) + ".wav"));
        }
    }
    else
    {
        lst->append(QUrl(AUDIO_ROOT_DIR + QString("%1").arg(intpart/100) + ".wav"));
        lst->append(QUrl(AUDIO_ROOT_DIR + "hundred.wav"));
        intpart = intpart%100;
        if (intpart < 21)
        {
            lst->append(QUrl(AUDIO_ROOT_DIR + QString("%1").arg(intpart) + ".wav"));
        }
        else
        {
            lst->append(QUrl(AUDIO_ROOT_DIR + QString("%1").arg(intpart - intpart%10) + ".wav"));
            if (intpart%10)
                lst->append(QUrl(AUDIO_ROOT_DIR + QString("%1").arg(intpart%10) + ".wav"));
        }
    }

    lst->append(QUrl(AUDIO_ROOT_DIR + "point.wav"));

    lst->append(QUrl(AUDIO_ROOT_DIR + QString("%1").arg(fracpart*10.0) + ".wav"));
}

void MainScreen::feedbackEnded(){
    playing_feedback = false;
}

void MainScreen::periodicFeedback(){
    if (workout)
    {
        counter++;

        Utils::realTimeFeedback->clear();

        QList<QUrl> fdbk = QList<QUrl>();
        fdbk.append(QUrl(AUDIO_ROOT_DIR+"exercise_time.wav"));
        feedbackAppendNumber(counter*2,&fdbk);
        fdbk.append(QUrl(AUDIO_ROOT_DIR+"minutes.wav"));

        Utils::realTimeFeedback->setQueue(fdbk);
        Utils::realTimeFeedback->play();
    }
    else
        counter = 0;
}

void MainScreen::detectChangeFeedback(){
    static bool play = false;
    QList<QUrl> fdbk = QList<QUrl>();
    if (workout)
    {
        spd_array[7] = speed;
        grd_array[7] = grade;

        if (spd_array[0]!=spd_array[1] && spd_array[1]==spd_array[2] && spd_array[2]==spd_array[3] && spd_array[3]==spd_array[4]
            && spd_array[4]==spd_array[5] && spd_array[5]==spd_array[6] && spd_array[6]==spd_array[7])
        {
            fdbk.append(QUrl(AUDIO_ROOT_DIR+"Current_Speed.wav"));
            feedbackAppendNumber(speed,&fdbk);
            if (Preferences::getMeasurementSystem())
                fdbk.append(QUrl(AUDIO_ROOT_DIR+"mph.wav"));
            else
                fdbk.append(QUrl(AUDIO_ROOT_DIR+"kph.wav"));
            play=true;
        }

        if (grd_array[0]!=grd_array[1] && grd_array[1]==grd_array[2] && grd_array[2]==grd_array[3] && grd_array[3]==grd_array[4]
            && grd_array[4]==grd_array[5] && grd_array[5]==grd_array[6] && grd_array[6]==grd_array[7])
        {
            fdbk.append(QUrl(AUDIO_ROOT_DIR+"Current_Grade.wav"));
            feedbackAppendNumber(grade,&fdbk);
            fdbk.append(QUrl(AUDIO_ROOT_DIR+"percent.wav"));
            play=true;
        }

        if (play)
        {
            Utils::realTimeFeedback->clear();
            Utils::realTimeFeedback->setQueue(fdbk);
            Utils::realTimeFeedback->play();
            play=false;
        }

        if (speed != last_speed || grade != last_grade)
            change = true;
        else
            change = false;

        if (change)
        {
            fdbk.append(QUrl(AUDIO_ROOT_DIR + "ding.wav"));
            Utils::realTimeFeedback->clear();
            Utils::realTimeFeedback->setQueue(fdbk);
            Utils::realTimeFeedback->play();

            if (speed!=step_current_speed)
            {
                speed_offset = (speed-step_current_speed);
            }
            if (grade!=step_current_grade)
            {
                grade_offset = (grade-step_current_grade);
            }

            if(this->recordingWorkout)
            {
                recordSpeedChange(speed);
                recordGradeChange(grade);
            }
        }
        last_speed = speed;
        last_grade = grade;
        for (int i=0;i<7;i++)
        {
            spd_array[i]=spd_array[i+1];
            grd_array[i]=grd_array[i+1];
        }
    }
    else
    {
        playing_feedback = false;
        for (int i=0;i<8;i++)
            spd_array[i]=grd_array[i]=0.0f;
    }
}

void MainScreen::CheckHeartRate(){
    if ( workout && workout->name.contains("Heart Rate") )
    {
        int _HR = Preferences::getAverageHeartRate();
        qDebug() << "Heart Rate:" << _HR;
        qDebug() << "min HR:" << workout->min_HR;
        qDebug() << "max HR:" << workout->max_HR;
        if (!grade_stage)
        {
            qDebug() << "Grade Stage:" << "Min HR";
            if ( (_HR - workout->min_HR) > 5 )
            {
                Preferences::setCurrentGrade(Preferences::getCurrentGrade() - 0.5f);
            }
            if ( (workout->min_HR - _HR) > 5 )
            {
                Preferences::setCurrentGrade(Preferences::getCurrentGrade() + 0.5f);
            }
        }
        else
        {
            qDebug() << "Grade Stage:" << "Max HR";
            if ( (_HR - workout->max_HR) > 5 )
            {
                Preferences::setCurrentGrade(Preferences::getCurrentGrade() - 0.5f);
            }
            if ( (workout->max_HR - _HR) > 5 )
            {
                Preferences::setCurrentGrade(Preferences::getCurrentGrade() + 0.5f);
            }
        }
    }
}

void MainScreen::updateDisplay(){

    if(isWorkoutPaused()){
        //do nothing
        return;
    }

    long elapsedTimeMillis = QDateTime::currentMSecsSinceEpoch() - startTime;
    long elapsedTime = elapsedTimeMillis/1000;

    if(elapsedTimeMillis >= nextWorkoutStepTime){
        processNextWorkoutStep();
    }

    minutes = elapsedTime/60;
    ui->elapsedTimeMinutesLabel->setText( QString("%1").arg(minutes,2,'g',-1,QLatin1Char('0')) );

    seconds = elapsedTime%60;
    ui->elapsedTimeSecondsLabel->setText(QString(":%1").arg(seconds,2,'g',-1,QLatin1Char('0')));

   // *****************************************************SET SPEED HERE!!!!************************************************************
    double intpart;
    double fracpart = modf(Preferences::getCurrentGrade(),&intpart);
    if (fracpart>0 && fracpart < 0.1)
        fracpart = 0.1;
    grade = intpart + fracpart;

    ui->gradeIntegerLabel->setText(QString("%1").arg(intpart,1,'g',-1,QLatin1Char('0')));
    ui->gradeDecimalLabel->setText(QString(".%1").arg(fracpart*10));

    fracpart = modf(Preferences::getCurrentSpeed(),&intpart);
    if (fracpart>0 && fracpart < 0.1)
        fracpart = 0.1;
    speed = intpart + fracpart;

    ui->speedIntegerLabel->setText(QString("%1").arg(intpart,1,'g',-1,QLatin1Char('0')));
    ui->speedDecimalLabel->setText(QString(".%1").arg(fracpart*10));

    heartRate = Preferences::getAverageHeartRate();
// *****************************************************SET SPEED HERE!!!!************************************************************


    // HEART RATE HERE

    QString heartRateText;
    if(heartRate == 0 || heartRate == MAX_HEART_RATE){
        heartRateText = "--";
    }
    else{
       heartRateText = QString("%1").arg(heartRate);
    }

    ui->heartRateLabel->setText(heartRateText);

    // END HEART RATE

    QString paceString;
    if (speed)
    {
        paceString = QString("%1").arg((int)(60.0f/speed));
        paceString.append(":");
        int intPaceSeconds = 60000.0f/speed;
        intPaceSeconds= (((intPaceSeconds)%1000)*6)/100;
        QString paceSecondsString;
        if (intPaceSeconds < 10)
            paceSecondsString = "0";

        paceSecondsString.append(QString("%1").arg(intPaceSeconds));
        paceString.append(paceSecondsString);
    }


    else
        paceString = QString("--");

     ui->paceLabel->setText(QString("%1").arg(paceString));

    //Update distance
    static long lastUpdate=0;
    if (lastUpdate==0)
        lastUpdate=QDateTime::currentMSecsSinceEpoch();
    long thisUpdate=QDateTime::currentMSecsSinceEpoch();

    long timeDifference=thisUpdate-lastUpdate;
    distance += ((((double)speed)/3600000)*(timeDifference));



    lastUpdate=thisUpdate;

    ui->distanceIntegerLabel->setText(QString("%1").arg(((int)distance)%100));
    ui->distanceDecimalLabel->setText(QString(".%1").arg(((int)(distance*100))%100,2,'g',-1,QLatin1Char('0')));

    //Update Time
    QDateTime currentTime = QDateTime::currentDateTime();
    QString time = currentTime.toString("h:mma");
    int splitLocation = time.length() - 2;
    ui->timeLabel->setText(time.left(splitLocation));
    ui->ampmLabel->setText(time.right(2) );
    ui->dateLabel->setText(currentTime.toString(QString("dddd, M/d/yy")));

    //update Calorie Counter
    calculateCalories(speed, grade, timeDifference);

    //update History Widgets
    if ((seconds==0 || seconds==30) && _update)
    {
        bumpHistoryWidgets();
        _update = false;
    }
    else
        if (seconds%30)
            _update = true;

    updateHistoryWidgets(speed, grade);

    updateScoreWidgetText(elapsedTime, speed, grade);
    if ( workout )
    {
        if ( workout->name.contains("Army") || workout->name.contains("Navy") || workout->name.contains("Marines") || workout->name.contains("Air Force") )
        {
            if(Preferences::getMeasurementSystem()){
                if ( distance >= workout->distance )
                    // We've completed the workout steps, and we're not recording, so end the workout.
                    Preferences::setCurrentState(0);
            }
            else
            {
                if ( distance >= (workout->distance)*1.609f )
                    // We've completed the workout steps, and we're not recording, so end the workout.
                    Preferences::setCurrentState(0);
            }
        }
    }

}

void MainScreen::updateScoreWidgetText(long time, float speed, float grade){
    if (workout)
    {
        int nextStepTime=nextWorkoutStepTime/1000;
        nextStepTime= nextStepTime-time;
        int scoreMinutes = nextStepTime/60;
        int scoreSeconds = nextStepTime%60;
        if (workout->name.contains("Fire Fighter"))
            stage=(nextWorkoutStepIndex-3)/2;
        else if (workout->name.contains("Fitness"))
            stage=(nextWorkoutStepIndex-1)/2;
        if (stage<0)
            stage=0;
        scoreWidget.setText( QString("You Are Currently In Stage: %1\n\nStage Time Remaining: %2:%3\n").arg(stage).arg(scoreMinutes,2,'g',-1,QLatin1Char('0')).arg(scoreSeconds,2,'g',-1,QLatin1Char('0'))
                             ,"");

    }
}

void MainScreen::calculateCalories(int speed, int grade, long timeDifference){

      float calSpeed=(double)speed*26.8224;
      float calGrade=(double)grade/100;
      float calTime=(float)timeDifference/60000;
      float calO2;
      if (calSpeed<99.24288)
          calO2=0.1f*calSpeed+1.8f*calSpeed*calGrade+3.5f;
      else
          calO2=0.2f*calSpeed+0.9f*calSpeed*calGrade+3.5f;

      calories+=calO2*weight*3.5f*(calTime/(float)1000.0);
      ui->caloriesLabel->setText(QString("%1").arg((int)calories));
}

void MainScreen::bumpHistoryWidgets(){
    for(int i=0;i<HISTORY_LENGTH-1;i++){
        speedHistory[i] = speedHistory[i+1];
        gradeHistory[i] = gradeHistory[i+1];
    }
}

void MainScreen::updateHistoryWidgets(int speed, int grade){

    if(Preferences::getMeasurementSystem())
    {
        speedHistory[HISTORY_LENGTH-1] = speed;
    }
    else
    {
        speedHistory[HISTORY_LENGTH-1] = speed/2;
    }
    gradeHistory[HISTORY_LENGTH-1] = grade;

        // I think this way was better than it is now.. maybe I'll change it back someday
//        speedHistory[HISTORY_LENGTH-1] = (speed*16)/(Utils::getMAX_SPEED());
//        gradeHistory[HISTORY_LENGTH-1] = (grade*16)/(MAX_GRADE);

//        qDebug() << "history: " << speed << ", " << grade;

        speedHistoryWidget.update();
        gradeHistoryWidget.update();
}

void MainScreen::updateRunningDudeImage(){
    float percentageAroundTrack = distance / TRACK_LENGTH;
    percentageAroundTrack -= (int) percentageAroundTrack;

    QString type;
    int imageCount;

    if (wheelchairDude){
        type="Push";
        imageCount=124;
    }
    else if(speed < Preferences::FAST_SPEED){ // What about RAMMING SPEED?!
        type= "Walk";
        imageCount = 149;
    }
    else if (speed < Preferences::JOGGING_SPEED){
       type = "Jog";
       imageCount = 99;
    }
    else {
       type = "Run";
       imageCount = 49;
    }


    double imageNumberDouble = percentageAroundTrack*imageCount + 1;
    int imageNumber = imageNumberDouble;
    float currentPosition=(float)imageNumber/(float)imageCount;

    if (currentPosition>lastPosition){
        QString imagePath = RUNNING_DUDE_IMAGE_PATH + "/" + type + "/" + type + QString("%1").arg(imageNumber) + ".png";
        QPixmap runningDudePixmap(imagePath);
        runningDudeWidget->setPixmap(runningDudePixmap);
        lastPosition=currentPosition;
        if (lastPosition==1)
            lastPosition=0;
    }

}

void MainScreen::on_audioButton_invisibleButton_pressed()
{
    audioSettingsWidget.setVisible(!audioSettingsWidget.isVisible());
    audioSettingsWidget.raise();
}

void MainScreen::on_track_invisibleButton_pressed()
{
    hideWidgets();

    trackWidget->show();
    runningDudeWidget->show();

    ui->wheelchairDudeImage->setVisible(true);
    ui->wheelchairDudeImage->raise();

    ui->wheelchairDude_invisibleButton->setVisible(true);
    ui->wheelchairDude_invisibleButton->raise();
}

void MainScreen::on_wheelchairDude_invisibleButton_pressed(){
//    qDebug()<< "wheelchair button pressed: "<< wheelchairDude;
    if (!wheelchairDude)
    {
        ui->wheelchairDudeImage->setPixmap(wheelchairDudeOn);
        wheelchairDude=true;
    }
    else
    {
        ui->wheelchairDudeImage->setPixmap(wheelchairDudeOff);
        wheelchairDude=false;
    }
}

void MainScreen::on_web_invisibleButton_pressed()
{
    hideWidgets();

    webview->show();
}

void MainScreen::on_trails_invisibleButton_pressed()
{
    hideWidgets();
    trailSelectionWidget.setVisible(true);
}

void MainScreen::on_tranquil_invisibleButton_pressed()
{
    hideWidgets();
    tranquilSelectionWidget.setVisible(true);
}

void MainScreen::playVideo(QString filename)
{
    hideWidgets();

    Phonon::MediaSource source(filename);
    player->play(source);
    player->setVisible(true);
    player->videoWidget()->show();
}

void MainScreen::showWorkoutVisualization()
{
    hideWidgets();

    if(workout->visualization == WEB_VISUALIZATION){
         webview->show();
    }
    else if(workout->visualization == VIDEO_VISUALIZATION){
        playVideo(workout->videoPath);
    }
    else if(workout->visualization == SCORE_VISUALIZATION){
        scoreWidget.setVisible(true);
        scoreWidget.setText(workout->scoreTitle, workout->scoreResults);
    }
    else{
        trackWidget->show();
        runningDudeWidget->show();
        ui->wheelchairDudeImage->setVisible(true);
        ui->wheelchairDudeImage->raise();
        ui->wheelchairDude_invisibleButton->setVisible(true);
        ui->wheelchairDude_invisibleButton->raise();
    }
}

void MainScreen::hideWidgets(void)
{
    webview->setVisible(false);
    trackWidget->hide();
    player->stop();
    player->videoWidget()->hide();
    player->setVisible(false);
    runningDudeWidget->hide();
    audioSettingsWidget.setVisible(false);
    tranquilSelectionWidget.setVisible(false);
    trailSelectionWidget.setVisible(false);
    scoreWidget.setVisible(false);
    ui->wheelchairDudeImage->setVisible(false);
    ui->wheelchairDudeImage->lower();
    ui->wheelchairDude_invisibleButton->setVisible(false);
    ui->wheelchairDude_invisibleButton->lower();
}

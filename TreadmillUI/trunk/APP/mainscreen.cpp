
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
#include "utils.h"
#include "time.h"
#include "screens.h"
#include "resultsscreen.h"

static int HISTORY_HEIGHT = 13;
static QString RUNNING_DUDE_IMAGE_PATH ="images/Running Dude";
static bool _update = false;

static float TRACK_LENGTH = .25; // in miles

void zero(int array[], int length){

    for(int i=0;i<length;i++){
        array[i] = 0;
    }
}

//static int *history;

static const int UPDATE_DISPLAY_DELAY = 100;
static const double HOURS_PER_UPDATE = ((double)UPDATE_DISPLAY_DELAY)/MILLIS_PER_HOUR;
//QTime LAST_UPDATE=currentTime();

MainScreen::MainScreen(QWidget *parent) :
    AbstractScreen(parent)
    ,ui(new Ui::MainScreen)
    ,secondTimer(new QTimer(this))
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
    ,videoMask(":/images/images/main_screen_large_video_mask.png")
    ,nextWorkoutStepIndex(0)
    ,nextWorkoutStepTime(0)
    ,workout(NULL)
    ,distance(0)
    ,speed(0)
    ,grade(0)
    ,heartRate(0)
    ,weight(0)
    ,recordingWorkout(FALSE)
    ,lastStepRecordedTime(0)
{
    ui->setupUi(this);
    setAttribute( Qt::WA_DeleteOnClose, false );

    //Put the background behind the player
    ui->backgroundLabel->lower();

    connect(secondTimer, SIGNAL(timeout()), this, SLOT( updateDisplay()));
    secondTimer->setSingleShot(false);
    secondTimer->setInterval(UPDATE_DISPLAY_DELAY);

    connect(milliSecondTimer, SIGNAL(timeout()), this, SLOT( updateRunningDudeImage()));
    milliSecondTimer->setSingleShot(false);
    milliSecondTimer->setInterval(10);

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
    player->videoWidget()->setScaleMode(Phonon::VideoWidget::ScaleAndCrop);
    player->videoWidget()->hide();
    connect(player, SIGNAL(finished()), this, SLOT(restartVideo()));

    audioSettingsWidget.setParent(this);
    audioSettingsWidget.move(centerPosition);
    audioSettingsWidget.setMask(videoMask.mask());
    audioSettingsWidget.setVisible(false);

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

    webview = new WebWidget(HOME_URL);
    webview->setParent(this);
    webview->hide();

    centerWidget.raise();
    audioSettingsWidget.raise();

//    Preferences::currentState.setOn();        // commented this out because it was causing a fault in the program (William)

    //    update the fields before the windows is initially displayed

    updateDisplay();
}

MainScreen* MainScreen::mainScreen = NULL;

void MainScreen::createMainScreen(QWidget* parent){
    mainScreen = new MainScreen(parent);
    mainScreen->hide();
}

MainScreen* MainScreen::getMainScreen(){
    return mainScreen;
}

void MainScreen::startWorkout(Workout* workout){
    startWorkout(workout, FALSE);
}

void MainScreen::recordWorkout(Workout* workout){

    lastStepRecordedTime = QDateTime::currentMSecsSinceEpoch();

    startWorkout(workout, TRUE);
}

void MainScreen::startWorkout(Workout* workout, bool recordWorkout){

    this->workout = workout;
    this->recordingWorkout = recordWorkout;

    weight = workout->_weight;

    startTime = QDateTime::currentMSecsSinceEpoch();
    distance = 0;
    nextWorkoutStepIndex = 0;
    nextWorkoutStepTime = 0;
    calories=0;

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

    updateDisplay();

    if(Preferences::isTestingMode()){
        Screens::show(this);
    }
    else{
        Preferences::setCurrentState(ON_OFF_MASK);
    }
}

void MainScreen::processNextWorkoutStep() {

    if(workout != NULL){

        QList<Step*>* steps = workout->steps;

        for( int i=nextWorkoutStepIndex;i<steps->length();i++){
            Step* step = steps->at(nextWorkoutStepIndex);
            nextWorkoutStepIndex++;

            if(step->getType() == SPEED_CHANGE_TYPE){
                ChangeSpeedStep* changeSpeedStep = (ChangeSpeedStep*) step;
                Preferences::setCurrentSpeed(changeSpeedStep->speed);
//                qDebug() << "Workout speed change: " << changeSpeedStep->speed;
            }
            else if(step->getType() == GRADE_CHANGE_TYPE){
                ChangeGradeStep* changeGradeStep = (ChangeGradeStep*) step;
                Preferences::setCurrentGrade(changeGradeStep->grade);
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
        }

        if(!recordingWorkout){
            // We've completed the workout steps, and we're not recording, so end the workout.
            Preferences::setCurrentState(ON_OFF_MASK);

            if(Preferences::isTestingMode()){
                endWorkout();
            }
        }
    }
}

void MainScreen::writeHistoryEntry(){

    QFile historyFile(Preferences::getCurrentHistoryPath());
    historyFile.open(QFile::Append);

    QTextStream stream(&historyFile);

    QDate today = QDate::currentDate();

    stream << QString("%1").arg(today.month());
    stream << '-' << QString("%1").arg(today.day());
    stream << '-' << QString("%1").arg(today.year());
    stream << "\t";

    stream << workout->name;
    stream << "\t";

    long elapsedTimeMillis = QDateTime::currentMSecsSinceEpoch() - startTime;
    long seconds = elapsedTimeMillis/1000;

    stream << seconds;
    stream << "\t";

    stream << calories;
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

    if(!eventConsumed){
        AbstractScreen::keyPressEvent(event);
    }
}

void MainScreen::recordSpeedChange(float speed){
    recordWaitStep();
    workout->steps->append(new ChangeSpeedStep(speed));
}

void MainScreen::recordGradeChange(float grade){
    recordWaitStep();
    workout->steps->append(new ChangeGradeStep(grade));
}

void MainScreen::closeEvent(QCloseEvent * event){
    //used for testing when the escape button is pressed
    endWorkout();
}

void MainScreen::endWorkout(){

//    Preferences::setCurrentState(0);        // turn the treadmill off
    hide();

    if(Preferences::isUsbDrivePresent()){
        writeHistoryEntry();

        if(recordingWorkout){
            recordWaitStep();
            workout->save();
        }
    }
    Preferences::currentWorkout=NULL;

    secondTimer->stop();
    milliSecondTimer->stop();
}

MainScreen::~MainScreen()
{
    delete workout;
    delete ui;

    player->stop();
    delete player;
    delete secondTimer;
    delete webview;
}

void MainScreen::restartVideo(){

    player->stop();
    player->play();
}


void MainScreen::updateDisplay(){

    long elapsedTimeMillis = QDateTime::currentMSecsSinceEpoch() - startTime;
    long elapsedTime = elapsedTimeMillis/1000;

    if(elapsedTimeMillis >= nextWorkoutStepTime){
        processNextWorkoutStep();
    }

    int minutes = elapsedTime/60;
    ui->elapsedTimeMinutesLabel->setText( QString("%1").arg(minutes,2,'g',-1,QLatin1Char('0')) );

    int seconds = elapsedTime%60;
    ui->elapsedTimeSecondsLabel->setText(QString(":%1").arg(seconds,2,'g',-1,QLatin1Char('0')));

   // *****************************************************SET SPEED HERE!!!!************************************************************
    double val;
    double fracpart = modf(Preferences::getCurrentGrade(),&val);
    if (fracpart>0 && fracpart < 0.1)
        fracpart = 0.1;

    ui->gradeIntegerLabel->setText(QString("%1").arg(val,1,'g',-1,QLatin1Char('0')));
    ui->gradeDecimalLabel->setText(QString(".%1").arg(fracpart*10));

    fracpart = modf(Preferences::getCurrentSpeed(),&val);
    if (fracpart>0 && fracpart < 0.1)
        fracpart = 0.1;

    ui->speedIntegerLabel->setText(QString("%1").arg(val,1,'g',-1,QLatin1Char('0')));
    ui->speedDecimalLabel->setText(QString(".%1").arg(fracpart*10));

    heartRate = Preferences::getAverageHeartRate();
// *****************************************************SET SPEED HERE!!!!************************************************************

    ui->heartRateLabel->setText(QString("%1").arg(heartRate));

    QString paceString;
    if (speed)
        paceString = QString("%1").arg(600/speed);
    else
        paceString = QString("--");
    paceString.append(":");
    int intPaceSeconds;
    if (speed)
        intPaceSeconds = ((60*1000)/speed);
    else
        intPaceSeconds = 0;
    intPaceSeconds=intPaceSeconds%100;
    intPaceSeconds=intPaceSeconds*.6;
    QString paceSecondsString;

    if (intPaceSeconds < 10)
        paceSecondsString = "0";

    paceSecondsString.append(QString("%1").arg(intPaceSeconds));
    paceString.append(paceSecondsString);

    ui->paceLabel->setText(QString("%1").arg(paceString));

    //Update distance
    static long lastUpdate=0;
    if (lastUpdate==0)
        lastUpdate=QDateTime::currentMSecsSinceEpoch();
    long thisUpdate=QDateTime::currentMSecsSinceEpoch();

    //distance += ((double)speed)*HOURS_PER_UPDATE/10; // this wasn't quite right.
    long timeDifference=thisUpdate-lastUpdate;
    distance += ((((double)speed/10)/3600000)*(timeDifference));

    if(workout != NULL && distance >= workout->distance){
        qDebug() << "wham " << minutes << ", " << seconds;
        QString message = QString("You completed the " + workout->name + " fitness test in %1 minutes and %2 seconds.").arg(minutes).arg(seconds);
        Screens::show(new ResultsScreen(NULL, message));
        endWorkout();
    }

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

}

void MainScreen::calculateCalories(int speed, int grade, long timeDifference){
//    qDebug() << "calculating Calories based on weight: " << weight << " speed: " << speed << " and grade: "<< grade ;

      float calSpeed=(double)speed*2.68224;
      float calGrade=(double)grade/1000;
      float calTime=(float)timeDifference/60000;
     // qDebug()<< "Time in mins: " << calTime;
      float calO2;
      if (calSpeed<99.24288)
          calO2=0.1f*calSpeed+1.8f*calSpeed*calGrade+3.5f;
      else
          calO2=0.2f*calSpeed+0.9f*calSpeed*calGrade+3.5f;


      calories+=calO2*weight*3.5f*(calTime/(float)1000.0);// calTime/1000
//    qDebug()<< "calTime: " <<calTime/(float)1000.0 ;

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
        speedHistory[HISTORY_LENGTH-1] = speed/10;
    }
    else
    {
        speedHistory[HISTORY_LENGTH-1] = speed/20;
    }
    gradeHistory[HISTORY_LENGTH-1] = grade/10;

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

    if(speed < Preferences::FAST_SPEED){
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

    QString imagePath = RUNNING_DUDE_IMAGE_PATH + "/" + type + "/" + type + QString("%1").arg(imageNumber) + ".png";
    QPixmap runningDudePixmap(imagePath);
    runningDudeWidget->setPixmap(runningDudePixmap);
}

void MainScreen::on_audioButton_invisibleButton_pressed()
{
    webview->hide();
    audioSettingsWidget.setVisible(!audioSettingsWidget.isVisible());
}

void MainScreen::on_track_invisibleButton_pressed()
{
    hideWidgets();

    trackWidget->show();
    runningDudeWidget->show();
}

void MainScreen::on_web_invisibleButton_pressed()
{
    hideWidgets();

    webview->setVisible(true);
}

void MainScreen::on_trails_invisibleButton_pressed()
{
    playVideo("trails.avi");
}

void MainScreen::on_tranquil_invisibleButton_pressed()
{
    playVideo("tranquil.avi");
}

void MainScreen::playVideo(QString filename)
{
    hideWidgets();

    Phonon::MediaSource source(filename);
    player->play(source);
    player->setVisible(true);
    player->videoWidget()->show();
}

void MainScreen::hideWidgets(void)
{
    webview->setVisible(false);
    trackWidget->hide();
    player->stop();
    player->videoWidget()->hide();
    player->setVisible(false);
    runningDudeWidget->hide();
}

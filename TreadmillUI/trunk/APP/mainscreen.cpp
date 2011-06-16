
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

MainScreen::MainScreen(QWidget *parent, Workout* workout) :
    AbstractScreen(parent)
    ,ui(new Ui::MainScreen)
    ,secondTimer(new QTimer(this))
    ,milliSecondTimer(new QTimer(this))
    ,playTimer(new QTimer(this))
    ,startTime(QDateTime::currentMSecsSinceEpoch())
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
    ,workout(workout)
    ,distance(0)
    ,speed(0)
    ,weight(workout->_weight)
{
    ui->setupUi(this);
    setAttribute( Qt::WA_DeleteOnClose );
    setAttribute(Qt::WA_InputMethodEnabled);

    if(Preferences::measurementSystem == STANDARD){
        ui->distanceMetricLabel->setText("mi");
        ui->paceMetricLabel->setText("(mins/mi)");
        ui->speedMetricLabel->setText("mph");
        Utils::setMAX_SPEED(MAX_SPEED_MPH);
        if (!weight)
            weight=72.5;
        else
            weight=weight*.45359237;
    }
    else {
        ui->distanceMetricLabel->setText("km");
        ui->paceMetricLabel->setText("(mins/km)");
        ui->speedMetricLabel->setText("km/h");
        Utils::setMAX_SPEED(MAX_SPEED_KPH);
        if (!weight)
            weight=72.5;
    }

    //Put the background behind the player
    ui->backgroundLabel->lower();

    connect(secondTimer, SIGNAL(timeout()), this, SLOT( updateDisplay()));
    secondTimer->setSingleShot(false);
    secondTimer->setInterval(UPDATE_DISPLAY_DELAY);
    secondTimer->start();

    connect(milliSecondTimer, SIGNAL(timeout()), this, SLOT( updateRunningDudeImage()));
    milliSecondTimer->setSingleShot(false);
    milliSecondTimer->setInterval(10);
    milliSecondTimer->start();

    //     add the history widgets
        zero(speedHistory, HISTORY_LENGTH);
        zero(gradeHistory, HISTORY_LENGTH);
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
    trackWidget->setPixmap(trackBitmap);
    trackWidget->show();

    runningDudeWidget->setFixedSize(centerSize);
    runningDudeWidget->show();


    webview = new WebWidget(HOME_URL);
    webview->setParent(&centerWidget);
    webview->hide();

//    webWidget.setMask(videoMask.mask());
//    webWidget.load(QUrl("http://google.com"));
    centerWidget.raise();

    Preferences::application->installEventFilter(this);

//    Preferences::currentState.setOn();        // commented this out because it was causing a fault in the program (William)

    //    update the fields before the windows is initially displayed

    updateDisplay();
}


void MainScreen::processNextWorkoutStep() {

    if(workout != NULL && workout->steps != NULL){

        QList<Step*>* steps = workout->steps;

        for( int i=nextWorkoutStepIndex;i<steps->length();i++){
            Step* step = steps->at(nextWorkoutStepIndex);
            nextWorkoutStepIndex++;

            if(step->getType() == SPEED_CHANGE_TYPE){
                ChangeSpeedStep* changeSpeedStep = (ChangeSpeedStep*) step;
                Preferences::setCurrentSpeed(changeSpeedStep->speed);
            }
            else if(step->getType() == GRADE_CHANGE_TYPE){
                ChangeGradeStep* changeGradeStep = (ChangeGradeStep*) step;
                Preferences::setCurrentGrade(changeGradeStep->grade);
            }
            else if(step->getType() == WAIT_TYPE){
                WaitStep* waitStep = (WaitStep*) step;
                nextWorkoutStepTime += waitStep->time;

                /**
                  * Return.  This method will get called again during updateDisplay()
                  * and will pick up where it left off.
                  */
                return;
            }
        }

        // We've completed the workout
        close();
    }
}

void MainScreen::writeHistoryEntry(){

    if(Preferences::isUsbDrivePresent()){
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
}

void MainScreen::closeEvent(QCloseEvent * event){

//    Preferences::currentState.setOff();           // Commented this out because of error in state (William)

    writeHistoryEntry();
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


bool MainScreen::eventFilter(QObject * watched, QEvent *event)
{
    if(event->type() == UPPER_BOARD_EVENT_TYPE){
        UpperBoardEvent* upperBoardEvent = (UpperBoardEvent*)event;

        ui->heartRateLabel->setText(QString("%1").arg(Preferences::getHeartRate()));
    }

    return QWidget::eventFilter(watched, event);
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
    ui->elapsedTimeMinutesLabel->setText( QString("%1").arg(minutes) );

    int seconds = elapsedTime%60;

    QString elapsedTimeSecondsString;

    if(seconds < 10){
       elapsedTimeSecondsString = "0";
    }

    elapsedTimeSecondsString.append(QString("%1").arg(seconds));

    ui->elapsedTimeSecondsLabel->setText(elapsedTimeSecondsString);

    QString secondsString = QString("%1").arg(elapsedTime);

   // *****************************************************SET SPEED HERE!!!!************************************************************
    //int grade = Preferences::getCurrentGrade();
    int grade=120; // use to force grade display
    ui->gradeIntegerLabel->setText(QString("%1").arg(grade/10));
    ui->gradeDecimalLabel->setText(QString("%1").arg(grade%10));

    //int speed = Preferences::getCurrentSpeed();
    speed=120; // use to force speed display
    ui->speedIntegerLabel->setText(QString("%1").arg(speed/10));
    ui->speedDecimalLabel->setText(QString("%1").arg(speed%10));

    Preferences::setHeartRate(180);  // use to force a heartrate
// *****************************************************SET SPEED HERE!!!!************************************************************
    QString paceString = QString("%1").arg(600/speed);
    paceString.append(":");

    int intPaceSeconds = ((60*1000)/speed);
    intPaceSeconds=intPaceSeconds%100;
    intPaceSeconds=intPaceSeconds*.6;
    QString paceSecondsString;

    if (intPaceSeconds < 10)
        paceSecondsString = "0";

    paceSecondsString.append(QString("%1").arg(intPaceSeconds));
    paceString.append(paceSecondsString);

    ui->paceLabel->setText(QString("%1").arg(paceString));

    calculateCalories(speed, grade, elapsedTime);

    //Update distance
    static long lastUpdate=0;
    if (lastUpdate==0)
        lastUpdate=QDateTime::currentMSecsSinceEpoch();
    long thisUpdate=QDateTime::currentMSecsSinceEpoch();

    //distance += ((double)speed)*HOURS_PER_UPDATE/10; // this wasn't quite right.
    distance += ((((double)speed/10)/3600000)*(thisUpdate-lastUpdate));
    lastUpdate=thisUpdate;
    int distanceInt = (int) distance;
    int distanceDecimal = (distance - distanceInt) * 100;

    QString distanceDecString;
    if (distanceDecimal<10)
        distanceDecString="0";

    distanceDecString.append(QString("%1").arg(distanceDecimal));
    ui->distanceIntegerLabel->setText(QString("%1").arg(distanceInt));
    ui->distanceDecimalLabel->setText(distanceDecString);

    //Update Time
    QDateTime currentTime = QDateTime::currentDateTime();
    QString time = currentTime.toString("h:mma");
    int splitLocation = time.length() - 2;
    ui->timeLabel->setText(time.left(splitLocation));
    ui->ampmLabel->setText(time.right(2) );
    ui->dateLabel->setText(currentTime.toString(QString("dddd, M/d/yy")));

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

void MainScreen::calculateCalories(int speed, int grade, long elapsedTime){
//    qDebug() << "calculating Calories based on weight: " << weight << " speed: " << speed << " and grade: "<< grade ;

      double calSpeed=(double)speed*2.68224;
      double calGrade=(double)grade/1000;
      double calTime=(double)elapsedTime/60;
      double calO2;
      if (calSpeed<99.24288)
          calO2=0.1*calSpeed+1.8*calSpeed*calGrade+3.5;
      else
          calO2=0.2*calSpeed+0.9*calSpeed*calGrade+3.5;
      calories=calO2*weight*3.5*(calTime/1000);

       ui->caloriesLabel->setText(QString("%1").arg(calories));
}

void MainScreen::bumpHistoryWidgets(){
    for(int i=0;i<HISTORY_LENGTH-1;i++){
        speedHistory[i] = speedHistory[i+1];
        gradeHistory[i] = gradeHistory[i+1];
    }
}

void MainScreen::updateHistoryWidgets(int speed, int grade){

    if(Preferences::measurementSystem == STANDARD)
    {
        speedHistory[HISTORY_LENGTH-1] = speed/10;
        gradeHistory[HISTORY_LENGTH-1] = grade/10;
    }
    else
    {
        speedHistory[HISTORY_LENGTH-1] = speed/20;
        gradeHistory[HISTORY_LENGTH-1] = grade/20;
    }

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
    webview->hide();

    player->stop();
    player->videoWidget()->hide();
    player->setVisible(false);

    trackWidget->show();
    runningDudeWidget->show();
}

void MainScreen::on_web_invisibleButton_pressed()
{
    // add code here for web browser
    player->stop();
    player->videoWidget()->hide();
    player->setVisible(false);

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
    webview->hide();

    trackWidget->hide();
    runningDudeWidget->hide();

    Phonon::MediaSource source(filename);
    player->play(source);
    player->setVisible(true);
    player->videoWidget()->show();
}

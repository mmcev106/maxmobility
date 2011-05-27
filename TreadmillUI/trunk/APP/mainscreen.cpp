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

static int HISTORY_HEIGHT =15;
static QString RUNNING_DUDE_IMAGE_PATH ="images/Running Dude";

void zero(int array[], int length){

    for(int i=0;i<length;i++){
        array[i] = 0;
    }
}

//static int *history;

static const int UPDATE_DISPLAY_DELAY = 1000;
static const double HOURS_PER_UPDATE = ((double)UPDATE_DISPLAY_DELAY)/MILLIS_PER_HOUR;

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
    ,speedHistoryWidget(this, speedHistory, HISTORY_LENGTH, HISTORY_HEIGHT, BIG_BRICK_URL, HIGHLIGHTED_BIG_BRICK_URL)
    ,gradeHistoryWidget(this, gradeHistory, HISTORY_LENGTH, HISTORY_HEIGHT, BIG_BRICK_URL, HIGHLIGHTED_BIG_BRICK_URL)
    ,player(new Phonon::VideoPlayer(Phonon::VideoCategory, this))
    ,audioSettingsWidget(NULL)
    ,videoMask(":/images/images/main_screen_large_video_mask.png")
    ,nextWorkoutStepIndex(0)
    ,nextWorkoutStepTime(0)
    ,workout(workout)
    ,distance(0)
{
    ui->setupUi(this);
    setAttribute( Qt::WA_DeleteOnClose );

    if(Preferences::measurementSystem == STANDARD){
        ui->distanceMetricLabel->setText("mi");
        ui->paceMetricLabel->setText("(mins/mi)");
        ui->speedMetricLabel->setText("mph");
        Utils::setMAX_SPEED(MAX_SPEED_MPH);
    }
    else {
        ui->distanceMetricLabel->setText("km");
        ui->paceMetricLabel->setText("(mins/km)");
        ui->speedMetricLabel->setText("km/h");
        Utils::setMAX_SPEED(MAX_SPEED_KPH);
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

    Preferences::setSpeedChangeFunction((reinterpret_cast<void (*)()>(&MainScreen::updateDisplay)));
    Preferences::setGradeChangeFunction((reinterpret_cast<void (*)()>(&MainScreen::updateDisplay)));

    //     add the history widgets
        zero(speedHistory, HISTORY_LENGTH);
        zero(gradeHistory, HISTORY_LENGTH);
        int historyY = 580;
        //int historyHeight=30;
        //int historyWidth=81;
        gradeHistoryWidget.move(25,historyY);
        speedHistoryWidget.move(930,historyY);
       // gradeHistoryWidget.resize ( historyWidth,historyHeight);
        //speedHistoryWidget.resize ( historyWidth,historyHeight);


        //gradeHistoryWidget.hide();        ** REMOVE HIDE HISTORY WIDGETS **
        //speedHistoryWidget.hide();

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
    QFile historyFile(HISTORY);
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

    stream << seconds; //TODO
    stream << "\t";

    stream << distance;
    stream << "\n";

    stream.flush();
    historyFile.close();
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
}

//void MainScreen::keyPressEvent(QKeyEvent* event){
//    if (event->key() == Qt::UpArrow){
//        Preferences::setCurrentSpeed(Preferences::getCurrentSpeed()+2);
//        Preferences::setCurrentGrade(Preferences::getCurrentGrade()+1);
//    }
//    else if (event->key() == Qt::DownArrow){
//        Preferences::setCurrentSpeed(Preferences::getCurrentSpeed()-2);
//        Preferences::setCurrentGrade(Preferences::getCurrentGrade()-1);
//    }

//    QWidget::keyPressEvent(event);
//}


bool MainScreen::eventFilter(QObject * watched, QEvent *event)
{
    if(event->type() == UPPER_BOARD_EVENT_TYPE){
        UpperBoardEvent* upperBoardEvent = (UpperBoardEvent*)event;

        ui->heartRateLabel->setText(QString("%1").arg((unsigned int)upperBoardEvent->heartRate));
//        ui->cadenceLabel->setText(QString("%1").arg((unsigned int)upperBoardEvent->cadence));
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

//    ui->heartRateLabel->setText(secondsString);
    ui->caloriesLabel->setText(secondsString);
//    ui->cadenceLabel->setText(secondsString);
    ui->paceLabel->setText(secondsString);

    float grade = Preferences::getCurrentGrade();
    int gradeInt = (int) grade;
    int gradeDecimal = (grade - gradeInt) * 10;
    ui->gradeIntegerLabel->setText(QString("%1").arg(gradeInt));
    ui->gradeDecimalLabel->setText(QString("%1").arg(gradeDecimal));

    double speed = Preferences::getCurrentSpeed();
    int speedInt = (int) speed;
    int speedDecimal = (speed - speedInt) * 10;
    ui->speedIntegerLabel->setText(QString("%1").arg(speedInt));
    ui->speedDecimalLabel->setText(QString("%1").arg(speedDecimal));


    distance += speed*HOURS_PER_UPDATE;
    int distanceInt = (int) distance;
    int distanceDecimal = (distance - distanceInt) * 10;

    ui->distanceIntegerLabel->setText(QString("%1").arg(distanceInt));
    ui->distanceDecimalLabel->setText(QString("%1").arg(distanceDecimal));

    QDateTime currentTime = QDateTime::currentDateTime();
    QString time = currentTime.toString("h:mma");
    int splitLocation = time.length() - 2;
    ui->timeLabel->setText(time.left(splitLocation));
    ui->ampmLabel->setText(time.right(2) );
    ui->dateLabel->setText(currentTime.toString(QString("dddd, M/d/yy")));

    if (seconds==0 || seconds==30)
        bumpHistoryWidgets();

    updateHistoryWidgets(speed, grade);

}

void MainScreen::bumpHistoryWidgets(){
    for(int i=0;i<HISTORY_LENGTH-1;i++){
        speedHistory[i] = speedHistory[i+1];
        gradeHistory[i] = gradeHistory[i+1];
    }
}

void MainScreen::updateHistoryWidgets(int speed, int grade){
    //1.609
    // only update history widgets every 30 secs

        speedHistory[HISTORY_LENGTH-1] = (speed*Utils::getMAX_SPEED())/16;
        gradeHistory[HISTORY_LENGTH-1] = grade*2;
//        if (gradeHistory[HISTORY_LENGTH-1] == 0)
//            gradeHistory[HISTORY_LENGTH-1] = 1;

        qDebug() << "history: " << speed << ", " << grade;

        speedHistoryWidget.update();
        gradeHistoryWidget.update();
}

void MainScreen::updateRunningDudeImage(){

        long elapsedTimeMillis = QDateTime::currentMSecsSinceEpoch() - startTime;

       long distanceTraveled = elapsedTimeMillis;
//       long speed = distanceTraveled/10;
       int trackLength = 30000;
       double dudePosition = distanceTraveled%trackLength;
       double percentageAroundTrack = dudePosition/trackLength;

       QString type;
       int imageCount;

//       if(speed < 6){
            type= "Walk";
            imageCount = 149;
//       }
//       else if (speed < 9){
//           type = "Jog";
//           imageCount = 99;
//       }
//       else {
//           type = "Run";
//           imageCount = 49;
//       }

//       qDebug() << "% around track: " << percentageAroundTrack;
       double imageNumberDouble = percentageAroundTrack*imageCount + 1;
//       qDebug() << "image # double: " << imageNumberDouble;
       int imageNumber = imageNumberDouble;

       QString imagePath = RUNNING_DUDE_IMAGE_PATH + "/" + type + "/" + type + QString("%1").arg(imageNumber) + ".png";
       QPixmap runningDudePixmap(imagePath);
       runningDudeWidget->setPixmap(runningDudePixmap);
}

void MainScreen::on_audioButton_invisibleButton_pressed()
{
    audioSettingsWidget.setVisible(!audioSettingsWidget.isVisible());
}

void MainScreen::on_track_invisibleButton_pressed()
{
    player->stop();
    player->videoWidget()->hide();
    player->setVisible(false);

    trackWidget->show();
    runningDudeWidget->show();
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
    trackWidget->hide();
    runningDudeWidget->hide();

    Phonon::MediaSource source(filename);
    player->play(source);
    player->setVisible(true);
    player->videoWidget()->show();
}

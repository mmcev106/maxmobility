#include "startupwindow.h"
#include "ui_startupwindow.h"

#include "heartratescreen.h"
#include "mainscreen.h"
#include "fitnesstestscreen.h"
#include "fatburnscreen.h"
#include "intervalscreen.h"
#include "myworkoutsscreen.h"
#include "screens.h"
#include <phonon/VideoWidget>
#include <QBitmap>
#include <QDir>
#include <QCoreApplication>
#include "preferences.h"
#include <QMessageBox>
#include "historyscreen.h"
#include "utils.h"`
#include "usbwarningscreen.h"
#include "outdoorpathsscreen.h"
#include "pointerevent.h"
#include "upperboardevent.h"
#include "calibrationscreen.h"
#include "settingsscreen.h"
#include "state.h"


using namespace std;

static int HILL_GRADE = 5;
static int STEEP_GRADE = MAX_GRADE;


StartupWindow::StartupWindow(QWidget *parent) :
    AbstractScreen(parent)
    ,ui(new Ui::StartupWindow)
    ,player(new VideoPlayer(this))
    ,sharedTimer(this)
{
    ui->setupUi(this);

    QSize playerSize(256,191);

    player->setFixedSize(playerSize);
    player->move(664,111);
//    player->videoWidget()->setScaleMode(Phonon::VideoWidget::ScaleAndCrop);
    player->videoWidget()->setFixedSize(playerSize);

    QPixmap pixmap(":/images/images/startup_sceen_video_mask.png");
    player->videoWidget()->setMask(pixmap.mask());

    Phonon::MediaSource *mediaSource = new Phonon::MediaSource("/videos/trails/radnor.avi");

    player->setVolume(0);
    player->play(*mediaSource);
    player->setVisible(true);
    player->show();

    connect(&sharedTimer, SIGNAL(timeout()), this, SLOT( sharedTimerTimeout()));
    sharedTimer.setInterval(250);
    sharedTimer.start();

    //hide the usbLabel by default
     ui->usbLabel->hide();

    //Put the background behind the player
    ui->backgroundLabel->lower();
    ui->invisibleButton->setFocusPolicy(Qt::NoFocus);

    Preferences::application->installEventFilter(this);
}

void StartupWindow::onSerialEvent(unsigned char* _data)
{

    unsigned char _state = _data[1] & (~STATE_CHANGE_MASK);

    unsigned char heartRate = _data[2];
    unsigned char speed = _data[3];
    unsigned char grade = _data[4];

    if (_state & ERROR_MASK)
    {
    }
    else
    {
        if (_state&UNITS_MASK)
            Preferences::setMeasurementSystem(STANDARD);
        else
            Preferences::setMeasurementSystem(METRIC);

        if (Preferences::getCurrentState() != _state)
        {
            // do state-based screen switching here!
            if (Preferences::getCurrentState()&CALIBRATING_MASK)
                CalibrationScreen::getCalibrationScreen()->setVisible(false);
            else if (Preferences::getCurrentState()&SETUP_MASK)
                SettingsScreen::getSettingsScreen()->setVisible(false);
            else if (Preferences::getCurrentState()&ON_OFF_MASK)
//                MainScreen::getMainScreen()->setVisible(false);
                MainScreen::getMainScreen()->endWorkout();
        }

        Preferences::updateCurrentState(_state);

        if ( _state&ON_OFF_MASK || ( !(_state&CALIBRATING_MASK) && !(_state&SETUP_MASK) ) )
        {
            Preferences::updateCurrentGrade(((float)grade)/10.0);
            Preferences::updateCurrentSpeed(((float)speed)/10.0);
            Preferences::setHeartRate(heartRate);
            if (_state&ON_OFF_MASK)
            {
                if (!MainScreen::getMainScreen()->isVisible())
                {
                    Screens::show( MainScreen::getMainScreen() );
                    if (Preferences::currentWorkout==NULL)
                    {
                        Preferences::currentWorkout = Workout::createWorkout("QStart", Utils::getDEF_SPEED(), 0, QUICK_WORKOUT_LENGTH);
                        MainScreen::getMainScreen()->startWorkout(Preferences::currentWorkout);
                    }
                }
            }
        }
        if ( _state&CALIBRATING_MASK )
        {
            if (!CalibrationScreen::getCalibrationScreen()->isVisible())
                CalibrationScreen::getCalibrationScreen()->setVisible(true);
            Preferences::updateCurrentGrade(((float)grade)/10.0);
        }
        if ( _state&SETUP_MASK )
        {
            if (!SettingsScreen::getSettingsScreen()->isVisible())
                SettingsScreen::getSettingsScreen()->setVisible(true);
            if ( _state&UNITS_MASK)
            {
                Preferences::setMeasurementSystem(STANDARD);
            }
            else
            {
                Preferences::setMeasurementSystem(METRIC);
            }
            if ( _data[2]&0x01 )
                Preferences::on_time = (((int)_data[3])*256) + (_data[4]);
            else
                Preferences::belt_time = (((int)(_data[3]))*256) + (_data[4]);
        }
    }
}

void StartupWindow::sharedTimerTimeout(){

    /**
      * This used to be done by connecting the finished() signal on the player,
      * but that did not work consistently.  Now this method is called on a timer.
      */
    if(player->currentTime() == player->totalTime()){
        player->seek(0);
        player->play();
    }

    if(Preferences::isUsbDrivePresent()){
        ui->usbLabel->show();
    }
    else{
        ui->usbLabel->hide();
    }
}

StartupWindow::~StartupWindow()
{
    delete ui;

    player->stop();
    delete player;
}

void StartupWindow::showMainScreen(QString name, float speed, float grade, int minutes){
    MainScreen::getMainScreen()->startWorkout(Workout::createWorkout(name, speed, grade, minutes));
}

void showUsbWarningScreen(){
    Screens::show(new UsbWarningScreen(":/images/images/Warning.png"));
    Utils::feedbackPlayer->stop();
}


void showUsbQuestionMarkScreen(){
    Screens::show(new UsbWarningScreen(":/images/images/(Question-Mark).png"));
    Utils::feedbackPlayer->stop();
}

void StartupWindow::on_invisibleButton_pressed()
{
    if(handleAccAction("walk.wav")){
        Preferences::currentWorkout = Workout::createWorkout("Walk", Preferences::WALKING_SPEED, 0, QUICK_WORKOUT_LENGTH);
        MainScreen::getMainScreen()->startWorkout(Preferences::currentWorkout);
        Utils::feedbackPlayer->stop();
    }
}

void StartupWindow::on_invisibleButton_2_pressed()
{
//    showMainScreen("Fast Walk", Preferences::FAST_SPEED, 0, QUICK_WORKOUT_LENGTH);
//    Workout* workout = Workout::createWorkout("Fast Walk", Preferences::FAST_SPEED, 0, QUICK_WORKOUT_LENGTH);
    Preferences::currentWorkout= Workout::createWorkout("Fast Walk", Preferences::FAST_SPEED, 0, QUICK_WORKOUT_LENGTH);
    MainScreen::getMainScreen()->startWorkout(Preferences::currentWorkout);
    Utils::feedbackPlayer->stop();
}

void StartupWindow::on_invisibleButton_3_pressed()
{
//    showMainScreen("Jog", Preferences::JOGGING_SPEED, 0, QUICK_WORKOUT_LENGTH);
    Preferences::currentWorkout= Workout::createWorkout("Jog",Preferences::JOGGING_SPEED,0,QUICK_WORKOUT_LENGTH);
    MainScreen::getMainScreen()->startWorkout(Preferences::currentWorkout);
    Utils::feedbackPlayer->stop();
}

void StartupWindow::on_invisibleButton_4_pressed()
{
//    showMainScreen("Run", Preferences::RUNNING_SPEED, 0, QUICK_WORKOUT_LENGTH);
    Preferences::currentWorkout= Workout::createWorkout("Run", Preferences::RUNNING_SPEED, 0, QUICK_WORKOUT_LENGTH);
    MainScreen::getMainScreen()->startWorkout(Preferences::currentWorkout);
    Utils::feedbackPlayer->stop();
}

void StartupWindow::on_invisibleButton_5_pressed()
{
//    showMainScreen("Hill Walk", Preferences::WALKING_SPEED, HILL_GRADE, QUICK_WORKOUT_LENGTH);
    Preferences::currentWorkout= Workout::createWorkout("Hill Walk", Preferences::WALKING_SPEED, HILL_GRADE, QUICK_WORKOUT_LENGTH);
    MainScreen::getMainScreen()->startWorkout(Preferences::currentWorkout);
    Utils::feedbackPlayer->stop();
}

void StartupWindow::on_invisibleButton_6_pressed()
{
//    showMainScreen("Steep Walk", Preferences::WALKING_SPEED, STEEP_GRADE, QUICK_WORKOUT_LENGTH);
    Preferences::currentWorkout= Workout::createWorkout("Steep Walk", Preferences::WALKING_SPEED, STEEP_GRADE, QUICK_WORKOUT_LENGTH);
    MainScreen::getMainScreen()->startWorkout(Preferences::currentWorkout);
    Utils::feedbackPlayer->stop();
}

void StartupWindow::on_invisibleButton_8_pressed()
{
    Screens::show(new IntervalScreen(0));
    Utils::feedbackPlayer->stop();
}

void StartupWindow::on_invisibleButton_10_pressed()
{

    Screens::show( new FatBurnScreen(0));
    Utils::feedbackPlayer->stop();
}

void StartupWindow::on_invisibleButton_9_pressed()
{
    Screens::show( new FitnessTestScreen(0));
    Utils::feedbackPlayer->stop();
}

//void StartupWindow::on_invisibleButton_14_pressed()
//{
//    //showMainScreen("USB");
//}

void StartupWindow::on_invisibleButton_11_pressed()
{
    if(Preferences::isUsbDrivePresent()){
        Screens::show(new MyWorkoutsScreen());
    }
    else{
        showUsbWarningScreen();
    }
    Utils::feedbackPlayer->stop();
}

void StartupWindow::on_invisibleButton_12_pressed()
{
    if(Preferences::isUsbDrivePresent()){
        Screens::show(new HistoryScreen());
    }
    else{
        showUsbWarningScreen();
    }
    Utils::feedbackPlayer->stop();
}

void StartupWindow::on_invisibleButton_13_pressed()
{
    showUsbQuestionMarkScreen();
    Utils::feedbackPlayer->stop();
}

void StartupWindow::on_outdoorPathsButton_pressed()
{
    Screens::show(new OutdoorPathsScreen());
    Utils::feedbackPlayer->stop();
}

void StartupWindow::on_invisibleButton_16_pressed()
{
    Screens::show( new HeartRateScreen(0));
    Utils::feedbackPlayer->stop();
}

void StartupWindow::on_acc_invisibleButton_pressed()
{
    Preferences::accessibilityMode = true;
    Utils::feedbackPlayer->play("C:/audio/Both_Instruction1.wav");
}

bool StartupWindow::event(QEvent *event)
{
    if(event->type() == POINTER_EVENT_TYPE){
        PointerEvent* pointerEvent = (PointerEvent*)event;

        if(pointerEvent->pointer == player){
            on_outdoorPathsButton_pressed();
        }
    }

    return AbstractScreen::event(event);
}



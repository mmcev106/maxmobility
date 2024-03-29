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

static const int AUDIO_LOOP_DELAY = 30;     // loop delay in seconds

StartupWindow::StartupWindow(QWidget *parent) :
    AbstractScreen(parent)
    ,ui(new Ui::StartupWindow)
    ,player(new VideoPlayer(this))
    ,sharedTimer(this)
    ,errorMessageScreen(NULL, "Error: ")
    ,mockData(NULL)
{
    ui->setupUi(this);

    QSize playerSize(259,194);

    player->setFixedSize(playerSize);
    player->move(664,111);
//    player->videoWidget()->setScaleMode(Phonon::VideoWidget::ScaleAndCrop);
    player->videoWidget()->setFixedSize(playerSize);

    QPixmap pixmap(":/images/images/startup_sceen_video_mask.png");
    player->videoWidget()->setMask(pixmap.mask());

    mediaSource = new Phonon::MediaSource("/videos/trails/radnor.avi");

    player->setVolume(0);
    player->play(*mediaSource);
    player->setVisible(true);
//    connect(player, SIGNAL(finished()), this, SLOT(restartVideo()));
    player->show();
    player->raise();

    connect(&sharedTimer, SIGNAL(timeout()), this, SLOT( sharedTimerTimeout()));
    sharedTimer.setInterval(250);
    sharedTimer.start();

    Utils::InitAudio(Preferences::startupWindow);
    connect(Utils::backgroundMusic, SIGNAL(finished()), this, SLOT(restartMusic()));

    //hide the usbLabel by default
     ui->usbLabel->hide();

    //Put the background behind the player
    ui->backgroundLabel->lower();
    ui->invisibleButton->setFocusPolicy(Qt::NoFocus);

    Preferences::application->installEventFilter(this);
}

void StartupWindow::restartVideo(){
//    player->stop();
    player->play(*mediaSource);
    player->seek(0);
}

void StartupWindow::restartMusic(){

    QList<QUrl> playlist = QList<QUrl>();
    playlist.append(QUrl(AUDIO_ROOT_DIR+"PL1.wav"));
    playlist.append(QUrl(AUDIO_ROOT_DIR+"PL2.wav"));
    playlist.append(QUrl(AUDIO_ROOT_DIR+"PL3.wav"));
    playlist.append(QUrl(AUDIO_ROOT_DIR+"PL4.wav"));
    playlist.append(QUrl(AUDIO_ROOT_DIR+"PL5.wav"));
    playlist.append(QUrl(AUDIO_ROOT_DIR+"PL6.wav"));

    Utils::backgroundMusic->setQueue(playlist);
    Utils::backgroundMusic->stop();
    Utils::backgroundMusic->play();
}
void StartupWindow::onSerialEvent(unsigned char* _data)
{
    static bool _workoutrunning = false;

    unsigned char _state = _data[1];

    unsigned char heartRate = _data[2];
    unsigned char speed = _data[3];
    unsigned char grade = _data[4];

    if (_state & ERROR_MASK)
    {
        _state &= ~STATE_CHANGE_MASK;
//        QString _err = QString("Error Code: %1\n").arg(_state);
        QString _err;
        if (_state&EM_STOP_ERROR_MASK)
        {
            _err.append("Replace safety magnet.\n");

            if(Utils::realTimeFeedback->state() != Phonon::PlayingState){
                Utils::realTimeFeedback->clear();

                QList<QUrl> fdbk = QList<QUrl>();
                fdbk.append(QUrl(AUDIO_ROOT_DIR+"Replace_Safety_Magnet.wav"));

                Utils::realTimeFeedback->setQueue(fdbk);
                Utils::realTimeFeedback->play();
            }
        }
        else
        {
            if (_state&TOE_SAFETY_ERROR_MASK)
            {
                _err.append("Toe saftey switch activated.\n");
            }
            else
            {
                if (_state&GRADE_CONTROL_ERROR_MASK)
                {
                    _err.append("Grade Control Error.\n");
                }
                else
                {
                    if (_state&SPEED_CONTROL_ERROR_MASK)
                    {
                        _err.append("Speed Control Error.\n");
                    }
                    else
                    {
                        if (_state&SERIAL_RECEIVING_ERROR_MASK)
                        {
                            _err.append("Serial Receive Error.\n");
                        }
                        else
                        {
                            if (_state&SERIAL_SENDING_ERROR_MASK)
                            {
                                _err.append("Serial Sending Error.\n");
                            }
                            else
                            {
                                if (_state&CRITICAL_ERROR_MASK)
                                {
                                    _err.append("Critical Error.\n");
                                }
                            }
                        }
                    }
                }
            }
        }
        _err.append("\nPress the Start Button to continue.");
        errorMessageScreen.setText(_err);
        MainScreen::getMainScreen()->pauseWorkout();
        Screens::show(&errorMessageScreen);
    }
    else
    {
        if (errorMessageScreen.isVisible())
            errorMessageScreen.hide();
        MainScreen::getMainScreen()->unPauseWorkout();
        _state &= ~STATE_CHANGE_MASK;

        if (_state&UNITS_MASK)
            Preferences::setMeasurementSystem(STANDARD);
        else
            Preferences::setMeasurementSystem(METRIC);


//        if (Preferences::getCurrentState() != _state)
//        {
//            // do state-based screen switching here!
//            if (Preferences::getCurrentState()&CALIBRATING_MASK)
//                CalibrationScreen::getCalibrationScreen()->setVisible(false);
//            else
//            {
//                if (Preferences::getCurrentState()&SETUP_MASK)
//                    SettingsScreen::getSettingsScreen()->setVisible(false);
//                else
//                {
//                    if (Preferences::getCurrentState()&ON_OFF_MASK)
//                    {
//                        MainScreen::getMainScreen()->endWorkout();
//                        qDebug() << "called end workout!";
//                    }
//                }
//            }
//        }

        Preferences::updateCurrentState(_state);

        if ( _state&ON_OFF_MASK || ( !(_state&CALIBRATING_MASK) && !(_state&SETUP_MASK) ) )
        {
            if (CalibrationScreen::getCalibrationScreen()->isVisible())
                CalibrationScreen::getCalibrationScreen()->setVisible(false);
            if (SettingsScreen::getSettingsScreen()->isVisible())
                SettingsScreen::getSettingsScreen()->setVisible(false);
            Preferences::updateCurrentGrade(((float)grade)/10.0);
            Preferences::updateCurrentSpeed(((float)speed)/10.0);
            Preferences::setHeartRate(heartRate);
            if (_state&ON_OFF_MASK)
            {
                if (!MainScreen::getMainScreen()->isVisible())
                {
                    _workoutrunning = true;
                    if (MainScreen::getWorkout()==NULL)
                    {
//                        MainScreen::getMainScreen()->defaultWorkout();
                        Workout* workout = Workout::createWorkout("Manual", Utils::getDEF_SPEED(), 0, QUICK_WORKOUT_LENGTH);
                        MainScreen::getMainScreen()->startWorkout(workout);
                    }
                    qDebug() << "showing main screen";
                    Screens::show( MainScreen::getMainScreen() );
                }
            }
            else
            {
                if (MainScreen::getMainScreen()->isVisible() && _workoutrunning)
                {
                    _workoutrunning = false;
                    qDebug() << "hiding main screen";
//                    MainScreen::getMainScreen()->hide();
                    MainScreen::getMainScreen()->endWorkout();
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

    Preferences::lastSerialMessageReceivedTime = QDateTime::currentMSecsSinceEpoch();
}

void StartupWindow::mockSerialEvent()
{
    qDebug() << "Sending mock serial event";

    if(mockData == NULL){
        mockData = new unsigned char[2];
        mockData[1] = SETUP_MASK;
    }

    /*if (mockData[1] == 0){
        mockData[1] = ERROR_MASK | EM_STOP_ERROR_MASK;
    }
    else{
        mockData[1] = 0;
    }*/

    onSerialEvent(mockData);
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

void StartupWindow::sharedTimerTimeout(){
    static int secondsPassed=0;
    unsigned char _state = Preferences::getCurrentState();
    if (!(_state & ON_OFF_MASK) && !(_state & CALIBRATING_MASK) && !(_state & SETUP_MASK) && !Preferences::accessibilityMode)
    {
        secondsPassed++;
        if (secondsPassed == 4*AUDIO_LOOP_DELAY)
        {
            secondsPassed=0;
    //        if (Utils::mediaObject->finished())
    //        {
                Utils::accFeedback->setCurrentSource(AUDIO_ROOT_DIR+"Pro_intro.wav");
                Utils::accFeedback->play();
    //        }
        }
    }
    else
        secondsPassed=0;

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
}


void showUsbQuestionMarkScreen(){
    Screens::show(new UsbWarningScreen(":/images/images/(Question-Mark).png"));
}

void StartupWindow::on_invisibleButton_pressed()
{
    if(handleAccAction("QS_Walk.wav")){
        Workout* workout = Workout::createWorkout("Walk", Preferences::WALKING_SPEED, 0, QUICK_WORKOUT_LENGTH);
        MainScreen::getMainScreen()->startWorkout(workout);
    }
}

void StartupWindow::on_invisibleButton_2_pressed()
{
    if(handleAccAction("QS_Fast_Walk.wav")){
        Workout* workout = Workout::createWorkout("Fast Walk", Preferences::FAST_SPEED, 0, QUICK_WORKOUT_LENGTH);
        MainScreen::getMainScreen()->startWorkout(workout);
    }
}

void StartupWindow::on_invisibleButton_3_pressed()
{
    if(handleAccAction("QS_Jog.wav")){
        Workout* workout = Workout::createWorkout("Jog",Preferences::JOGGING_SPEED,0,QUICK_WORKOUT_LENGTH);
        MainScreen::getMainScreen()->startWorkout(workout);
    }
}

void StartupWindow::on_invisibleButton_4_pressed()
{
    if(handleAccAction("QS_Run.wav")){
        Workout* workout = Workout::createWorkout("Run", Preferences::RUNNING_SPEED, 0, QUICK_WORKOUT_LENGTH);
        MainScreen::getMainScreen()->startWorkout(workout);
    }
}

void StartupWindow::on_invisibleButton_5_pressed()
{
    if(handleAccAction("QS_Hill.wav")){
        Workout* workout = Workout::createWorkout("Hill Walk", Preferences::WALKING_SPEED, HILL_GRADE, QUICK_WORKOUT_LENGTH);
        MainScreen::getMainScreen()->startWorkout(workout);
    }
}

void StartupWindow::on_invisibleButton_6_pressed()
{
    if(handleAccAction("QS_Steep_Hill.wav")){
        Workout* workout = Workout::createWorkout("Steep Walk", Preferences::WALKING_SPEED, STEEP_GRADE, QUICK_WORKOUT_LENGTH);
        MainScreen::getMainScreen()->startWorkout(workout);
    }
}

void StartupWindow::on_invisibleButton_8_pressed()
{
    if(handleAccAction("Program_Interval_Training.wav")){
        Screens::show(new IntervalScreen(0));
    }
}

void StartupWindow::on_invisibleButton_10_pressed()
{
    if(handleAccAction("Program_Fat_Burn.wav"))
        Screens::show( new FatBurnScreen(0));
}

void StartupWindow::on_invisibleButton_9_pressed()
{
    if(handleAccAction("Program_Fitness_Tests.wav"))
        Screens::show( new FitnessTestScreen(0));
}

void StartupWindow::on_invisibleButton_11_pressed()
{
    if(handleAccAction("My_Workout_USB.wav"))
    {
        if(Preferences::isUsbDrivePresent()){
            Screens::show(new MyWorkoutsScreen());
        }
        else{
            showUsbWarningScreen();
        }
    }
}

void StartupWindow::on_invisibleButton_12_pressed()
{
    if(handleAccAction("My_Workout_History.wav"))
    {
        if(Preferences::isUsbDrivePresent()){
            Screens::show(new HistoryScreen());
        }
        else{
            showUsbWarningScreen();
        }
    }
}

void StartupWindow::on_invisibleButton_13_pressed()
{
    showUsbQuestionMarkScreen();
}

void StartupWindow::on_outdoorPathsButton_pressed()
{
    if(handleAccAction("Program_Interval_Training.wav"))
        Screens::show(new OutdoorPathsScreen());
}

void StartupWindow::on_invisibleButton_16_pressed()
{
    if(handleAccAction("Program_HR_Control.wav"))
        Screens::show( new HeartRateScreen(0));
}

void StartupWindow::on_acc_invisibleButton_pressed()
{
    Preferences::accessibilityMode = true;
//    Utils::mediaObject->setCurrentSource(AUDIO_ROOT_DIR+"Pro_Full_Audio.wav");
    Utils::feedbackOutput->setVolume(70.0/100.0);

    Utils::accFeedback->clear();
    QList<QUrl> fdbk = QList<QUrl>();
    fdbk.append(QUrl(AUDIO_ROOT_DIR+"Pro_Instruction1.wav"));
    fdbk.append(QUrl(AUDIO_ROOT_DIR+"Pro_Instruction2.wav"));
    fdbk.append(QUrl(AUDIO_ROOT_DIR+"Both_Instruction3.wav"));
    fdbk.append(QUrl(AUDIO_ROOT_DIR+"Both_Instruction4.wav"));
    fdbk.append(QUrl(AUDIO_ROOT_DIR+"Both_Instruction5.wav"));
    Utils::accFeedback->setQueue(fdbk);

    Utils::accFeedback->play();
}

//bool StartupWindow::event(QEvent *event)
//{
//    if(event->type() == POINTER_EVENT_TYPE){
//        PointerEvent* pointerEvent = (PointerEvent*)event;

//        if(pointerEvent->pointer == player){
//            on_outdoorPathsButton_pressed();
//        }
//    }

//    return AbstractScreen::event(event);
//}



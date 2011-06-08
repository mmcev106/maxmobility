#include "startupwindow.h"
#include "ui_startupwindow.h"
#include "testwidget.h"

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
#include "testwidget.h"
#include "utils.h"`
#include "usbwarningscreen.h"

using namespace std;

static int QUICK_WORKOUT_LENGTH = 30; //minutes
static int HILL_GRADE = 5;
static int STEEP_GRADE = MAX_GRADE;


StartupWindow::StartupWindow(QWidget *parent) :
    AbstractScreen(parent)
    ,ui(new Ui::StartupWindow)
    ,player(new Phonon::VideoPlayer(Phonon::VideoCategory, this))
    ,sharedTimer(this)
{
    ui->setupUi(this);

    QSize playerSize(256,191);

    player->setFixedSize(playerSize);
    player->move(664,111);
    player->videoWidget()->setScaleMode(Phonon::VideoWidget::ScaleAndCrop);

    QPixmap pixmap(":/images/images/startup_sceen_video_mask.png");
    player->videoWidget()->setMask(pixmap.mask());

    Phonon::MediaSource *mediaSource = new Phonon::MediaSource("trails.avi");

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
    Screens::show( new MainScreen(this, Workout::createWorkout(name, speed, grade, minutes)));
}

void showUsbWarningScreen(){
    Screens::show(new UsbWarningScreen(":/images/images/Warning.png"));
}


void showUsbQuestionMarkScreen(){
    Screens::show(new UsbWarningScreen(":/images/images/(Question-Mark).png"));
}

void StartupWindow::on_invisibleButton_pressed()
{
    //walk
    showMainScreen("Walk", Preferences::WALKING_SPEED, 0, QUICK_WORKOUT_LENGTH);
}

void StartupWindow::on_invisibleButton_2_pressed()
{
    //fast
    showMainScreen("Fast Walk", Preferences::FAST_SPEED, 0, QUICK_WORKOUT_LENGTH);
}

void StartupWindow::on_invisibleButton_3_pressed()
{
    //jog
    showMainScreen("Jog", Preferences::JOGGING_SPEED, 0, QUICK_WORKOUT_LENGTH);
}

void StartupWindow::on_invisibleButton_4_pressed()
{
    //run
    showMainScreen("Run", Preferences::RUNNING_SPEED, 0, QUICK_WORKOUT_LENGTH);
}

void StartupWindow::on_invisibleButton_5_pressed()
{
    //hill
    showMainScreen("Hill Walk", Preferences::WALKING_SPEED, HILL_GRADE, QUICK_WORKOUT_LENGTH);
}

void StartupWindow::on_invisibleButton_6_pressed()
{
    //steep
    showMainScreen("Steep Walk", Preferences::WALKING_SPEED, STEEP_GRADE, QUICK_WORKOUT_LENGTH);
}

void StartupWindow::on_invisibleButton_8_pressed()
{
    Screens::show(new IntervalScreen(0));
}

void StartupWindow::on_invisibleButton_10_pressed()
{

    Screens::show( new FatBurnScreen(0));
}

void StartupWindow::on_invisibleButton_9_pressed()
{
    Screens::show( new FitnessTestScreen(0));
}

void StartupWindow::on_invisibleButton_14_pressed()
{
    //showMainScreen("USB");
}

void StartupWindow::on_invisibleButton_11_pressed()
{
    if(Preferences::isUsbDrivePresent()){
        Screens::show(new MyWorkoutsScreen());
    }
    else{
        showUsbWarningScreen();
    }
}

void StartupWindow::on_invisibleButton_12_pressed()
{
    if(Preferences::isUsbDrivePresent()){
        Screens::show(new HistoryScreen());
    }
    else{
        showUsbWarningScreen();
    }
}

void StartupWindow::on_invisibleButton_13_pressed()
{
    showUsbQuestionMarkScreen();
}

void StartupWindow::on_invisibleButton_15_pressed()
{
    //showMainScreen("Video");
}

void StartupWindow::on_invisibleButton_16_pressed()
{
    Screens::show( new HeartRateScreen(0));
}

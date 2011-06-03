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

using namespace std;

static int QUICK_WORKOUT_LENGTH = 30; //minutes
static int WALKING_SPEED;
static int FAST_SPEED;  // these are set in the constructor
static int JOGGING_SPEED;
static int RUNNING_SPEED;
static int HILL_GRADE = 5;
static int STEEP_GRADE = MAX_GRADE;


StartupWindow::StartupWindow(QWidget *parent) :
    AbstractScreen(parent)
    ,ui(new Ui::StartupWindow)
    ,player(new Phonon::VideoPlayer(Phonon::VideoCategory, this))
    ,videoRestartTimer(this)
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

    connect(&videoRestartTimer, SIGNAL(timeout()), this, SLOT( restartVideo()));
    videoRestartTimer.setInterval(250);
    videoRestartTimer.start();

    //Put the background behind the player
    ui->backgroundLabel->lower();
    ui->invisibleButton->setFocusPolicy(Qt::NoFocus);

    int maxSpeed;
    // Load default values from preferences
    if (Preferences::measurementSystem == STANDARD)
        maxSpeed=MAX_SPEED_MPH;
    else
        maxSpeed=MAX_SPEED_KPH;

    WALKING_SPEED=maxSpeed/4;
    FAST_SPEED=maxSpeed/2;
    JOGGING_SPEED=maxSpeed*.75;
    RUNNING_SPEED=maxSpeed;
}

void StartupWindow::restartVideo(){

    /**
      * This used to be done by connecting the finished() signal on the player,
      * but that did not work consistently.  Now this method is called on a timer.
      */
    if(player->currentTime() == player->totalTime()){
        player->seek(0);
        player->play();
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

void StartupWindow::on_invisibleButton_pressed()
{
    //walk
    showMainScreen("Walk", WALKING_SPEED, 0, QUICK_WORKOUT_LENGTH);
}

void StartupWindow::on_invisibleButton_2_pressed()
{
    //fast
    showMainScreen("Fast Walk", FAST_SPEED, 0, QUICK_WORKOUT_LENGTH);
}

void StartupWindow::on_invisibleButton_3_pressed()
{
    //jog
    showMainScreen("Jog", JOGGING_SPEED, 0, QUICK_WORKOUT_LENGTH);
}

void StartupWindow::on_invisibleButton_4_pressed()
{
    //run
    showMainScreen("Run", RUNNING_SPEED, 0, QUICK_WORKOUT_LENGTH);
}

void StartupWindow::on_invisibleButton_5_pressed()
{
    //hill
    showMainScreen("Hill Walk", WALKING_SPEED, HILL_GRADE, QUICK_WORKOUT_LENGTH);
}

void StartupWindow::on_invisibleButton_6_pressed()
{
    //steep
    showMainScreen("Steep Walk", WALKING_SPEED, STEEP_GRADE, QUICK_WORKOUT_LENGTH);
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
    Screens::show(new MyWorkoutsScreen());
}

void StartupWindow::on_invisibleButton_12_pressed()
{
    Screens::show(new HistoryScreen());
}

void StartupWindow::on_invisibleButton_13_pressed()
{
    //showMainScreen("Help");
}

void StartupWindow::on_invisibleButton_15_pressed()
{
    //showMainScreen("Video");
}

void StartupWindow::on_invisibleButton_16_pressed()
{
    Screens::show( new HeartRateScreen(0));
}

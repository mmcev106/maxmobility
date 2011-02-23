#include "startupwindow.h"
#include "ui_startupwindow.h"
#include "testwidget.h"

#include "mainscreen.h"
#include "heartratescreen.h"
#include "fitnesstestscreen.h"
#include "fatburnscreen.h"
#include "intervalscreen.h"
#include "myworkoutsscreen.h"
#include "screens.h"
//#include <phonon/VideoWidget>
#include <QBitmap>
#include <QDir>
#include <QCoreApplication>
#include "preferences.h"
#include <QMessageBox>

#include "testwidget.h"

using namespace std;

StartupWindow::StartupWindow(QWidget *parent) :
    AbstractScreen(parent)
    ,ui(new Ui::StartupWindow)
//    ,player(new Phonon::VideoPlayer(Phonon::VideoCategory, this))
{
    ui->setupUi(this);

//    player->setFixedSize(240,189);
//    player->move(673,112);
//    player->videoWidget()->setScaleMode(Phonon::VideoWidget::ScaleAndCrop);

//    QPixmap pixmap(":/images/images/startup_screen_video_mask.png");
//    player->setMask(pixmap.mask());

/*    Phonon::MediaSource *mediaSource = new Phonon::MediaSource("test video.avi");

    player->setVolume(0);
    player->play(*mediaSource);
    player->setVisible(true);
    player->show();

    connect(player, SIGNAL(finished()), this, SLOT(restartVideo()));
*/
    //Put the background behind the player
    ui->backgroundLabel->lower();

//    showMainScreen("Video");
}

void StartupWindow::restartVideo(){

//    player->stop();
//    player->play();
}

StartupWindow::~StartupWindow()
{
    delete ui;

//    player->stop();
//    delete player;
}

void StartupWindow::showMainScreen(QString action){
    qDebug() << "User Pressed: " << action;
    Screens::show( new MainScreen(0, action));
}

void QWidget::keyPressEvent(QKeyEvent* event){
    int key = event->key();

    if (key == Qt::Key_Escape){
        close();
    }
    else if (key == Qt::Key_M){
        if(Preferences::measurementSystem == STANDARD){
            Preferences::measurementSystem = METRIC;
            QMessageBox::about(this, "", "The measurement system has been changed to metric.");
        }
        else{
            Preferences::measurementSystem = STANDARD;
            QMessageBox::about(this, "", "The measurement system has been changed to standard.");
        }
    }
}

void StartupWindow::on_invisibleButton_pressed()
{
     showMainScreen("walk");
}

void StartupWindow::on_invisibleButton_2_pressed()
{
    showMainScreen("fast");
}

void StartupWindow::on_invisibleButton_3_pressed()
{
    showMainScreen("jog");
}

void StartupWindow::on_invisibleButton_4_pressed()
{
    showMainScreen("run");
}

void StartupWindow::on_invisibleButton_5_pressed()
{
    showMainScreen("hill");
}

void StartupWindow::on_invisibleButton_6_pressed()
{
    showMainScreen("steep");
}

void StartupWindow::on_invisibleButton_7_pressed()
{
    showMainScreen("HR Control");
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
    showMainScreen("USB");
}

void StartupWindow::on_invisibleButton_11_pressed()
{
    Screens::show(new MyWorkoutsScreen());
}

void StartupWindow::on_invisibleButton_12_pressed()
{
    showMainScreen("History");
}

void StartupWindow::on_invisibleButton_13_pressed()
{
    showMainScreen("Help");
}

void StartupWindow::on_invisibleButton_15_pressed()
{
    showMainScreen("Video");
}

void StartupWindow::on_invisibleButton_16_pressed()
{
    Screens::show( new HeartRateScreen(0));
}

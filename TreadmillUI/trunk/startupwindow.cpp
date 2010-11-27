#include "startupwindow.h"
#include "ui_startupwindow.h"

#include "mainscreen.h"
#include "heartratescreen.h"
#include "fitnesstestscreen.h"
#include <phonon/VideoWidget>
#include <QBitmap>
#include <QDir>
#include <QCoreApplication>

using namespace std;

StartupWindow::StartupWindow(QWidget *parent) :
    QWidget(parent)
    ,ui(new Ui::StartupWindow)
    ,player(new Phonon::VideoPlayer(Phonon::VideoCategory, this))
{
    ui->setupUi(this);

    player->setFixedSize(240,189);
    player->move(673,112);
//    player->videoWidget()->setScaleMode(Phonon::VideoWidget::ScaleAndCrop);

//    QPixmap pixmap(":/images/images/startup_screen_video_mask.png");
//    player->setMask(pixmap.mask());

    Phonon::MediaSource *mediaSource = new Phonon::MediaSource("test video.avi");

    player->setVolume(0);
    player->play(*mediaSource);
    player->setVisible(true);
    player->show();

    connect(player, SIGNAL(finished()), this, SLOT(restartVideo()));

    //Put the background behind the player
    QWidget *backgroundLabel = qFindChild<QWidget*>(this, "backgroundLabel");
    backgroundLabel->lower();

//    showMainScreen("Video");
}

void StartupWindow::restartVideo(){

    player->stop();
    player->play();
}

StartupWindow::~StartupWindow()
{
    delete ui;

    player->stop();
    delete player;
}

void StartupWindow::showMainScreen(QString action){
    qDebug() << "User Pressed: " << action;
    MainScreen *mainScreen = new MainScreen(0, action);
    mainScreen->show();
}

void QWidget::keyPressEvent(QKeyEvent* event){
    if (event->key() == Qt::Key_Escape){
        close();
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
    showMainScreen("Interval Training");
}

void StartupWindow::on_invisibleButton_10_pressed()
{
    showMainScreen("Fat Burn");
}

void StartupWindow::on_invisibleButton_9_pressed()
{
    FitnessTestScreen* w = new FitnessTestScreen(0);
     w->show();
}

void StartupWindow::on_invisibleButton_14_pressed()
{
    showMainScreen("USB");
}

void StartupWindow::on_invisibleButton_11_pressed()
{
    showMainScreen("Workouts");
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
    HeartRateScreen* w = new HeartRateScreen(0);
     w->show();
}

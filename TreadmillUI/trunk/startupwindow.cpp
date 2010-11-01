#include "startupwindow.h"
#include "ui_startupwindow.h"

#include "exercise_hills.h"
#include "videotest.h"
#include <phonon/VideoWidget>
#include <QBitmap>

using namespace std;

StartupWindow::StartupWindow(QWidget *parent) :
    QWidget(parent)
    ,ui(new Ui::StartupWindow)
    ,player(new Phonon::VideoPlayer(Phonon::VideoCategory, this))
{
    ui->setupUi(this);

    player->setFixedSize(QSize(212,212));
    player->move(567,121);
    player->videoWidget()->setScaleMode(Phonon::VideoWidget::ScaleAndCrop);

    QPixmap pixmap(":/images/images/startup_screen_video_mask.png");
    player->setMask(pixmap.mask());


    Phonon::MediaSource *mediaSource = new Phonon::MediaSource("/test video.avi");

    player->setVolume(0);
    player->play(*mediaSource);
    player->setVisible(true);
    player->show();

    //Put the background behind the player
    QWidget *backgroundLabel = qFindChild<QWidget*>(this, "backgroundLabel");
    backgroundLabel->lower();

    connect(player, SIGNAL(finished()), this, SLOT(restartVideo()));
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


void showMainScreen(QString action){
    qDebug() << action;
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
    showMainScreen("Fitness Tests");
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


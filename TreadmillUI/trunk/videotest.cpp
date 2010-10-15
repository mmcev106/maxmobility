#include "videotest.h"
#include "ui_videotest.h"
#include <Phonon/VideoPlayer>
#include <QTimer>
#include <QUrl>
#include <iostream>

using namespace std;

static int FRAME_RATE = 24;
static int DEFAULT_PAUSE_BETWEEN_FRAMES = 1000/FRAME_RATE;

VideoTest::VideoTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoTest),
    player(new Phonon::VideoPlayer(Phonon::VideoCategory, this)),
    timer(new QTimer(this)),
    videoSpeed(1.0)  //1.0 is normal
{
    ui->setupUi(this);

    setAttribute( Qt::WA_DeleteOnClose );




    player->setFixedSize(QSize(400,300));


    Phonon::MediaSource *mediaSource = new Phonon::MediaSource("/test video.avi");

    player->play(*mediaSource);
    player->setVisible(true);
    player->move(100,100);
    player->show();

    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));

    connect(player, SIGNAL(finished()), this, SLOT(play()));

    timer->setSingleShot(false);
    timer->setInterval(DEFAULT_PAUSE_BETWEEN_FRAMES);

    qDebug() << "Playing video.....";

}

void VideoTest::nextFrame(){

    int pauseBetweenFrames = DEFAULT_PAUSE_BETWEEN_FRAMES*videoSpeed;
    long newTime = player->currentTime() + pauseBetweenFrames;

//    qDebug() << "Skipping to time: " << newTime;

    if(newTime > player->totalTime()){
        newTime = 0;
    }

    player->seek(newTime);
}

void VideoTest::play(){
    qDebug() << "Restarting playback";
    player->stop();
//    player->seek(0);
    player->play();
}

VideoTest::~VideoTest()
{
    delete ui;


    player->stop();
    delete player;
}

void VideoTest::ensureManualPlayback(){

    if(player->isPlaying()){
        player->pause();
        timer->start();
    }
}


void VideoTest::on_pushButton_clicked()
{
    videoSpeed *= 1.4;
    qDebug() << "Video speed: " << videoSpeed;

    ensureManualPlayback();
}

void VideoTest::on_pushButton_2_clicked()
{
    videoSpeed *= .6;
    qDebug() << "Video speed: " << videoSpeed;

    ensureManualPlayback();
}


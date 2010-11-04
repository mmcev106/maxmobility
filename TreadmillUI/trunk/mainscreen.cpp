#include "mainscreen.h"
#include "ui_mainscreen.h"
#include <QStringBuilder>
#include <QDateTime>
#include <phonon/VideoWidget>
#include <QBitmap>

MainScreen::MainScreen(QWidget *parent, QString action) :
    QWidget(parent)
    ,ui(new Ui::MainScreen)
    ,secondTimer(new QTimer)
    ,elapsedTime(0)
    ,player(new Phonon::VideoPlayer(Phonon::VideoCategory, this))
{
    ui->setupUi(this);

    if(action.compare("Video") == 0){
        player->setFixedSize(QSize(528,396));
        player->move(249,93);
        player->videoWidget()->setScaleMode(Phonon::VideoWidget::ScaleAndCrop);

        QPixmap pixmap(":/images/images/main_screen_large_video_mask.png");
        player->setMask(pixmap.mask());

        Phonon::MediaSource *mediaSource = new Phonon::MediaSource("/test video.avi");

        player->setVolume(0);
        player->play(*mediaSource);
        player->setVisible(true);
        player->show();
    }

    connect(secondTimer, SIGNAL(timeout()), this, SLOT( secondElapsed()));
    secondTimer->setSingleShot(false);
    secondTimer->setInterval(1000);
    secondTimer->start();

    //update the fields before the windows is initially displayed
    secondElapsed();

    //Put the background behind the player
    QWidget *backgroundLabel = qFindChild<QWidget*>(this, "backgroundLabel");
    backgroundLabel->lower();
}

MainScreen::~MainScreen()
{
    delete ui;
    deleteLater();
}

void MainScreen::secondElapsed(){
    QString elapsedTimeString;
    int minutes = elapsedTime/60;
    int seconds = elapsedTime%60;
    elapsedTimeString.append(QString("%1").arg(minutes));
    elapsedTimeString.append(":");

    if(seconds < 10){
        elapsedTimeString.append("0");
    }

    elapsedTimeString.append(QString("%1").arg(seconds));

    ui->elapsedTimeLabel->setText(elapsedTimeString);

    QString secondsString = QString("%1").arg(elapsedTime);

    ui->heartRateLabel->setText(secondsString);
    ui->caloriesLabel->setText(secondsString);
    ui->cadenceLabel->setText(secondsString);
    ui->elevationGainLabel->setText(secondsString);
    ui->paceLabel->setText(secondsString);

    QString pointNumber;
    if(elapsedTime < 10){
        pointNumber.append("0");
    }
    else{
        pointNumber.append(QString("%1").arg(elapsedTime/10));
    }

    pointNumber.append(".");
    pointNumber.append(QString("%1").arg(elapsedTime%10));

    ui->distanceLabel->setText(pointNumber);
    ui->gradeLabel->setText(pointNumber);
    ui->speedLabel->setText(pointNumber);

    QDateTime currentTime = QDateTime::currentDateTime();
    QString time = currentTime.toString("h:mma");
    int splitLocation = time.length() - 2;
    ui->timeLabel->setText(time.left(splitLocation));
    ui->ampmLabel->setText(time.right(2) );
    ui->dateLabel->setText(currentTime.toString(QString("dddd, M/d/yy")));

    elapsedTime++;
}

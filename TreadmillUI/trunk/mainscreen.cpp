#include "mainscreen.h"
#include "ui_mainscreen.h"
#include <QStringBuilder>
#include <QDateTime>
#include <phonon/VideoWidget>
#include <QBitmap>

static int HISTORY_HEIGHT =31;

void zero(int array[], int length){

    for(int i=0;i<length;i++){
        array[i] = 0;
    }
}

MainScreen::MainScreen(QWidget *parent, QString action) :
    QWidget(parent)
    ,ui(new Ui::MainScreen)
    ,secondTimer(new QTimer)
    ,playTimer(new QTimer)
    ,elapsedTime(0)
    ,player(new Phonon::VideoPlayer(Phonon::VideoCategory, this))
    ,speedHistoryWidget(this, speedHistory, HISTORY_LENGTH, HISTORY_HEIGHT)
    ,gradeHistoryWidget(this, gradeHistory, HISTORY_LENGTH, HISTORY_HEIGHT)
{
    ui->setupUi(this);
    setAttribute( Qt::WA_DeleteOnClose );

    //Put the background behind the player
    QWidget *backgroundLabel = qFindChild<QWidget*>(this, "backgroundLabel");
    backgroundLabel->lower();





    connect(secondTimer, SIGNAL(timeout()), this, SLOT( updateDisplay()));
    secondTimer->setSingleShot(false);
    secondTimer->setInterval(1000);
    secondTimer->start();

    //update the fields before the windows is initially displayed
    updateDisplay();

    // add the history widgets
    zero(speedHistory, HISTORY_LENGTH);
    zero(gradeHistory, HISTORY_LENGTH);
    gradeHistoryWidget.move(36,528);
    speedHistoryWidget.move(664,528);

    ui->videoThumb->setPixmap(QPixmap("test video_thumb.jpg"));
    QPixmap thumbMask(":/images/images/video_thumb_mask.png");
    ui->videoThumb->setMask(thumbMask.mask());

    if(action.compare("Video") == 0){
        /* We must use a timer to start playback to allow this method to finish before setting the scale.
           The scale is not set properly otherwise. */

        connect(playTimer, SIGNAL(timeout()), this, SLOT( on_videoThumbButton_invisibleButton_pressed()));
        playTimer->setInterval(0);
        playTimer->setSingleShot(true);
        playTimer->start();
    }
}

MainScreen::~MainScreen()
{
    delete ui;

    player->stop();
    delete player;
    delete secondTimer;
}

void MainScreen::playVideo(){

    player->play(Phonon::MediaSource("test video.avi"));

    player->move(249,103);

    player->setVisible(true);
    player->show();

    player->setFixedSize(528,396);
    player->videoWidget()->setFixedSize(528,396);
    player->videoWidget()->setScaleMode(Phonon::VideoWidget::ScaleAndCrop);




    QPixmap pixmap(":/images/images/main_screen_large_video_mask.png");
    player->setMask(pixmap.mask());


//    player->setVolume(0);





}

void MainScreen::updateDisplay(){
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

    for(int i=0;i<HISTORY_LENGTH-1;i++){
        speedHistory[i] = speedHistory[i+1];
        gradeHistory[i] = gradeHistory[i+1];
    }

    speedHistory[HISTORY_LENGTH-1] = elapsedTime%31;
    gradeHistory[HISTORY_LENGTH-1] = elapsedTime%31;

    speedHistoryWidget.update();
    gradeHistoryWidget.update();

    elapsedTime++;
}

void MainScreen::on_videoThumbButton_invisibleButton_pressed()
{
    qDebug() << "asdf";
    playVideo();

}

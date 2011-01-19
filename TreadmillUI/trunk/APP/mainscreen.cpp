#include "mainscreen.h"
#include "ui_mainscreen.h"
#include <QStringBuilder>
#include <QDateTime>
//#include <phonon/VideoWidget>
//#include <phonon/MediaObject>
#include <QBitmap>
#include <QPainter>
#include "preferences.h"

static int HISTORY_HEIGHT =31;

void zero(int array[], int length){

    for(int i=0;i<length;i++){
        array[i] = 0;
    }
}

static int *history;

/*class VideoWrapper : public Phonon::VideoWidget
{

    const static int length = 31;

    const static int VERTICAL_PADDING = 1;
    const static int HORIZONTAL_PADDING = 3;
    const static int SQUARE_WIDTH = 8;
    const static int SQUARE_HEIGHT = 4;

public:
    VideoWrapper(QWidget *parent) :
            VideoWidget( parent)
    {
    }

    void paintEvent(QPaintEvent *){
//        QPainter qpainter (this);

//        qDebug() << "foo";
//        QColor myColor(0,0,0,0);
//        qpainter.fillRect(10,10, SQUARE_WIDTH, SQUARE_HEIGHT, myColor.blue());

//        for(int i=0;i<length;i++){
//            int x = i*(SQUARE_WIDTH+HORIZONTAL_PADDING);
//            int y = height() - SQUARE_HEIGHT;

//            if(y<=0){
//                qDebug() << "y is bad!";
//            }

//            QColor color(255,255,255, 50);
//            int squares = history[i];

//            while(squares > 0){

//                qpainter.fillRect(x,y, SQUARE_WIDTH, SQUARE_HEIGHT, color);

//                y -= SQUARE_HEIGHT+VERTICAL_PADDING;
//                color.setAlpha(color.alpha()+6);

//                squares--;
//            }
//        }
    }
};
*/
MainScreen::MainScreen(QWidget *parent, QString action) :
    QWidget(parent)
    ,ui(new Ui::MainScreen)
    ,secondTimer(new QTimer)
    ,playTimer(new QTimer)
    ,elapsedTime(0)
//    ,player(new Phonon::VideoPlayer(Phonon::VideoCategory, this))
//    ,speedHistoryWidget(this, speedHistory, HISTORY_LENGTH, HISTORY_HEIGHT, BIG_BRICK_URL, HIGHLIGHTED_BIG_BRICK_URL)
//    ,gradeHistoryWidget(this, gradeHistory, HISTORY_LENGTH, HISTORY_HEIGHT, BIG_BRICK_URL, HIGHLIGHTED_BIG_BRICK_URL)
    ,audioSettingsWidget(this)
{
    ui->setupUi(this);
    setAttribute( Qt::WA_DeleteOnClose );

    if(Preferences::measurementSystem == STANDARD){
        ui->distanceMetricLabel->setText("mi");
        ui->paceMetricLabel->setText("(mins/mi)");
        ui->speedMetricLabel->setText("mph");
    }
    else {
        ui->distanceMetricLabel->setText("km");
        ui->paceMetricLabel->setText("(mins/km)");
        ui->speedMetricLabel->setText("km/h");
    }

    //Put the background behind the player
    ui->backgroundLabel->lower();

//    Phonon::MediaObject *media = new Phonon::MediaObject(this);
//    VideoWrapper *test = new VideoWrapper(this);
//    Phonon::createPath(media, test);
//    media->setCurrentSource(Phonon::MediaSource("test video.avi"));
//    media->play();

    connect(secondTimer, SIGNAL(timeout()), this, SLOT( updateDisplay()));
    secondTimer->setSingleShot(false);
    secondTimer->setInterval(1000);
    secondTimer->start();

//    update the fields before the windows is initially displayed
    updateDisplay();

//     add the history widgets
//    zero(speedHistory, HISTORY_LENGTH);
//    zero(gradeHistory, HISTORY_LENGTH);
//    gradeHistoryWidget.move(36,528);
//    speedHistoryWidget.move(664,528);

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


    audioSettingsWidget.move(140, 108);
    audioSettingsWidget.setVisible(false);
}

MainScreen::~MainScreen()
{
    delete ui;

//    player->stop();
//    delete player;
    delete secondTimer;
}

//void MainScreen::keyPressEvent(QKeyEvent* event){
//    if (event->key() == Qt::Key_Escape){
//        close();
//    }
//}

void MainScreen::playVideo(){

//    player->play(Phonon::MediaSource("test video.avi"));

//    player->move(0,0);

//    player->setVisible(true);
//    player->show();

//    player->setFixedSize(528,396);
//    player->videoWidget()->setFixedSize(528,396);
//    player->videoWidget()->setScaleMode(Phonon::VideoWidget::ScaleAndCrop);




//    QPixmap pixmap(":/images/images/main_screen_large_video_mask.png");
//    player->setMask(pixmap.mask());

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

//    for(int i=0;i<HISTORY_LENGTH-1;i++){
//        speedHistory[i] = speedHistory[i+1];
//        gradeHistory[i] = gradeHistory[i+1];
//    }

//    speedHistory[HISTORY_LENGTH-1] = elapsedTime%HISTORY_HEIGHT;
//    gradeHistory[HISTORY_LENGTH-1] = elapsedTime%HISTORY_HEIGHT;

//    speedHistoryWidget.update();
//    gradeHistoryWidget.update();

    elapsedTime++;
}

void MainScreen::on_videoThumbButton_invisibleButton_pressed()
{
    qDebug() << "asdf";
    playVideo();

}

void MainScreen::on_audioButton_invisibleButton_pressed()
{
    audioSettingsWidget.setVisible(!audioSettingsWidget.isVisible());
}

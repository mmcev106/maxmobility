#include "mainscreen.h"
#include "ui_mainscreen.h"
#include <QStringBuilder>
#include <QDateTime>
//#include <phonon/VideoWidget>
//#include <phonon/MediaObject>
#include <QBitmap>
#include <QPainter>
#include "preferences.h"
#include <QDir>
#include "upperboardevent.h"

static int HISTORY_HEIGHT =31;
static QString RUNNING_DUDE_IMAGE_PATH ="/images/Running Dude";

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
    AbstractScreen(parent)
    ,ui(new Ui::MainScreen)
    ,secondTimer(new QTimer)
    ,milliSecondTimer(new QTimer)
    ,playTimer(new QTimer)
    ,elapsedTime(0)
    ,elapsedTimeMillis(0)
    ,trackWidget(new QLabel(this))
    ,runningDudeWidget(new QLabel(this))
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

    connect(milliSecondTimer, SIGNAL(timeout()), this, SLOT( updateRunningDudeImage()));
    milliSecondTimer->setSingleShot(false);
    milliSecondTimer->setInterval(10);
    milliSecondTimer->start();

//    update the fields before the windows is initially displayed
    updateDisplay();

//     add the history widgets
//    zero(speedHistory, HISTORY_LENGTH);
//    zero(gradeHistory, HISTORY_LENGTH);
//    gradeHistoryWidget.move(36,528);
//    speedHistoryWidget.move(664,528);

//    ui->videoThumb->setPixmap(QPixmap("test video_thumb.jpg"));
//    QPixmap thumbMask(":/images/images/video_thumb_mask.png");
//    ui->videoThumb->setMask(thumbMask.mask());

    if(action.compare("Video") == 0){
        /* We must use a timer to start playback to allow this method to finish before setting the scale.
           The scale is not set properly otherwise. */

        connect(playTimer, SIGNAL(timeout()), this, SLOT( on_videoThumbButton_invisibleButton_pressed()));
        playTimer->setInterval(0);
        playTimer->setSingleShot(true);
        playTimer->start();
    }

    QPoint centerPosition(137, 105);

    audioSettingsWidget.move(centerPosition);
    audioSettingsWidget.setVisible(false);

    QPixmap trackBitmap(RUNNING_DUDE_IMAGE_PATH + "/Track_Background.png");
    trackWidget->setFixedSize(trackBitmap.size());
    trackWidget->move(centerPosition);
    trackWidget->setPixmap(trackBitmap);
    trackWidget->show();
    trackWidget->lower();

    runningDudeWidget->show();
    runningDudeWidget->move(centerPosition);
    runningDudeWidget->setFixedSize(trackBitmap.size());

    Preferences::application->installEventFilter(this);

    Preferences::currentState.setOn();
}

void MainScreen::closeEvent(QCloseEvent * event){
    Preferences::currentState.setOff();
}

MainScreen::~MainScreen()
{
    delete ui;

//    player->stop();
//    delete player;
    delete secondTimer;
}

//void MainScreen::keyPressEvent(QKeyEvent* event){
//    if (event->key() == Qt::UpArrow){
//        Preferences::setCurrentSpeed(Preferences::getCurrentSpeed()+2);
//        Preferences::setCurrentGrade(Preferences::getCurrentGrade()+1);
//    }
//    else if (event->key() == Qt::DownArrow){
//        Preferences::setCurrentSpeed(Preferences::getCurrentSpeed()-2);
//        Preferences::setCurrentGrade(Preferences::getCurrentGrade()-1);
//    }

//    QWidget::keyPressEvent(event);
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

bool MainScreen::eventFilter(QObject * watched, QEvent *event)
{
    if(event->type() == UPPER_BOARD_EVENT_TYPE){
        UpperBoardEvent* upperBoardEvent = (UpperBoardEvent*)event;

        ui->heartRateLabel->setText(QString("%1").arg((unsigned int)upperBoardEvent->heartRate));
//        ui->cadenceLabel->setText(QString("%1").arg((unsigned int)upperBoardEvent->cadence));
    }

    return QWidget::eventFilter(watched, event);
}


void MainScreen::updateDisplay(){

    int minutes = elapsedTime/60;
    ui->elapsedTimeMinutesLabel->setText( QString("%1").arg(minutes) );

    int seconds = elapsedTime%60;

    QString elapsedTimeSecondsString;

    if(seconds < 10){
       elapsedTimeSecondsString = "0";
    }

    elapsedTimeSecondsString.append(QString("%1").arg(seconds));

    ui->elapsedTimeSecondsLabel->setText(elapsedTimeSecondsString);

    QString secondsString = QString("%1").arg(elapsedTime);

//    ui->heartRateLabel->setText(secondsString);
    ui->caloriesLabel->setText(secondsString);
//    ui->cadenceLabel->setText(secondsString);
    ui->paceLabel->setText(secondsString);

    ui->distanceIntegerLabel->setText(QString("%1").arg(elapsedTime/10));
    ui->distanceDecimalLabel->setText(QString("%1").arg(elapsedTime%10));

//    unsigned int grade = Preferences::getCurrentGrade();
//    QString gradeString = QString("%1.%2").arg(grade/10, grade%10);
//    ui->gradeLabel->setText(gradeString);

//    unsigned int speed = Preferences::getCurrentSpeed();
//    QString speedString = QString("%1.%2").arg(speed/10, speed%10);
//    ui->speedLabel->setText(speedString);

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

void MainScreen::updateRunningDudeImage(){

       long distanceTraveled = elapsedTimeMillis;
       long speed = distanceTraveled/10;
       int trackLength = 30000;
       double dudePosition = distanceTraveled%trackLength;
       double percentageAroundTrack = dudePosition/trackLength;

       QString type;
       int imageCount;

//       if(speed < 6){
            type= "Walk";
            imageCount = 149;
//       }
//       else if (speed < 9){
//           type = "Jog";
//           imageCount = 99;
//       }
//       else {
//           type = "Run";
//           imageCount = 49;
//       }

//       qDebug() << "% around track: " << percentageAroundTrack;
       double imageNumberDouble = percentageAroundTrack*imageCount + 1;
//       qDebug() << "image # double: " << imageNumberDouble;
       int imageNumber = imageNumberDouble;

       QString imagePath = RUNNING_DUDE_IMAGE_PATH + "/" + type + "/" + type + QString("%1").arg(imageNumber) + ".png";
//       qDebug() << "image path: " + imagePath;
       QPixmap runningDudePixmap(imagePath);
       runningDudeWidget->setPixmap(runningDudePixmap);

       elapsedTimeMillis+=10;
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

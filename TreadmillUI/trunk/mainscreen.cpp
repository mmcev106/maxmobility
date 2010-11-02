#include "mainscreen.h"
#include "ui_mainscreen.h"
#include <QStringBuilder>
#include <QDateTime>

MainScreen::MainScreen(QWidget *parent, QString action) :
    QWidget(parent),
    ui(new Ui::MainScreen)
    ,secondTimer(new QTimer)
    ,elapsedTime(0)
{
    ui->setupUi(this);

    connect(secondTimer, SIGNAL(timeout()), this, SLOT( secondElapsed()));
    secondTimer->setSingleShot(false);
    secondTimer->setInterval(1000);
    secondTimer->start();

    //update the fields before the windows is initially displayed
    secondElapsed();
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


    QDateTime currentTime = QDateTime::currentDateTime();
    QString time = currentTime.toString("h:mma");
    int splitLocation = time.length() - 2;
    ui->timeLabel->setText(time.left(splitLocation));
    ui->ampmLabel->setText(time.right(2) );
    ui->dateLabel->setText(currentTime.toString(QString("dddd, M/d/yy")));

    elapsedTime++;
}

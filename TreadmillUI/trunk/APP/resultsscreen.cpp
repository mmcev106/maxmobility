#include "resultsscreen.h"
#include "ui_resultsscreen.h"

ResultsScreen::ResultsScreen(QWidget *parent, QString message) :
    QWidget(parent),
    ui(new Ui::ResultsScreen)
    ,secondTimer(new QTimer(this))
{
    ui->setupUi(this);

    ui->messageLabel->setText(message);

    connect(secondTimer, SIGNAL(timeout()), this, SLOT( secondTimerTimeout()));
    secondTimer->setSingleShot(false);
    secondTimer->setInterval(1000);
    secondTimer->start();

    ui->closeButton->setVisible(false);
}

ResultsScreen::~ResultsScreen()
{
    delete ui;
}


void ResultsScreen::on_closeButton_pressed(){
    close();
}


void ResultsScreen::secondTimerTimeout()
{
    static int counter = 0;
    counter++;
    if (counter==FIRST_TIMEOUT)
    {
        ui->closeButton->setVisible(true);
        ui->closeLabel->setVisible(false);
    }
    if (counter==CLOSE_TIMEOUT)
    {
        secondTimer->stop();
        close();
    }
}

#include "resultsscreen.h"
#include "ui_resultsscreen.h"

ResultsScreen::ResultsScreen(QWidget *parent, QString message) :
    QWidget(parent),
    ui(new Ui::ResultsScreen)
{
    ui->setupUi(this);

    ui->messageLabel->setText(message);
}

ResultsScreen::~ResultsScreen()
{
    delete ui;
}


void ResultsScreen::on_closeButton_pressed(){
    close();
}

#include "mainscreen.h"
#include "ui_mainscreen.h"

MainScreen::MainScreen(QWidget *parent, QString action) :
    QWidget(parent),
    ui(new Ui::MainScreen)
{
    ui->setupUi(this);

}

MainScreen::~MainScreen()
{
    delete ui;
    deleteLater();
}

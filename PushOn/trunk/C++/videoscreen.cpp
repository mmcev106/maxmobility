#include "videoscreen.h"
#include "ui_videoscreen.h"

VideoScreen::VideoScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoScreen)
{
    ui->setupUi(this);
}

VideoScreen::~VideoScreen()
{
    delete ui;
}

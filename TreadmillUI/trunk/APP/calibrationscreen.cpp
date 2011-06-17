#include "calibrationscreen.h"
#include "ui_calibrationscreen.h"

CalibrationScreen* CalibrationScreen::calibrationScreen = NULL;

CalibrationScreen::CalibrationScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalibrationScreen)
{
    ui->setupUi(this);
}

CalibrationScreen::~CalibrationScreen()
{
    delete ui;
}


void CalibrationScreen::createCalibrationScreen(QWidget *parent){
    calibrationScreen = new CalibrationScreen(parent);
    calibrationScreen->hide();
}

CalibrationScreen* CalibrationScreen::getCalibrationScreen(){
    return calibrationScreen;
}

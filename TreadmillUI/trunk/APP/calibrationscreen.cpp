#include "calibrationscreen.h"
#include "ui_calibrationscreen.h"
#include "preferences.h"

CalibrationScreen* CalibrationScreen::calibrationScreen = NULL;
static const int UPDATE_DISPLAY_DELAY = 100;
int CalibrationScreen::grade=0;

CalibrationScreen::CalibrationScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalibrationScreen)
    ,secondTimer(new QTimer(this))
{
    connect(secondTimer, SIGNAL(timeout()), this, SLOT( updateDisplay()));
    secondTimer->setSingleShot(false);
    secondTimer->setInterval(UPDATE_DISPLAY_DELAY);
    secondTimer->start();

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

void CalibrationScreen::updateDisplay(){

    grade = (Preferences::getCurrentGrade()*10.0f);
    ui->gradeIntegerLabel->setText(QString("%1").arg(grade/10,1,'g',-1,QLatin1Char('0')));
    ui->gradeDecimalLabel->setText(QString(".%1").arg(grade%10,1,'g',-1,QLatin1Char('0')));
}

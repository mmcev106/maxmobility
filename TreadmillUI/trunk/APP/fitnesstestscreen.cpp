#include "fitnesstestscreen.h"
#include "ui_fitnesstestscreen.h"

#include "mainscreen.h"
#include "preferences.h"
#include "screens.h"
#include <QMessageBox>

static int SLIDER_X = 13;

FitnessTestScreen::FitnessTestScreen(QWidget *parent) :
    AbstractScreen(parent),
    ui(new Ui::FitnessTestScreen)
    ,weightSlider(this)
    ,ageSlider(this)
    ,initialSpeedSlider(this)
{
    ui->setupUi(this);
    setAttribute( Qt::WA_DeleteOnClose );

    initialSpeedSlider.move(SLIDER_X,437);
    on_invisibleButton_fitness_pressed();

    ui->backgroundLabel->lower();

    if(Preferences::gender == MALE){
        on_invisibleButton_maleRadio_pressed();
    }
    else{
        on_invisibleButton_femaleRadio_pressed();
    }
}

FitnessTestScreen::~FitnessTestScreen()
{
    delete ui;
}

void FitnessTestScreen::on_invisibleButton_5_pressed()
{
    close();
}

void FitnessTestScreen::on_invisibleButton_6_pressed()
{
    QMessageBox::information(this, "", "This feature is not yet implemented!");
}

void FitnessTestScreen::showTwoSliders(){

    initialSpeedSlider.hide();

    ageSlider.move(SLIDER_X,479);
    weightSlider.move(SLIDER_X,598);
}

void FitnessTestScreen::showThreeSliders(){

    initialSpeedSlider.show();

    ageSlider.move(SLIDER_X,556);
    weightSlider.move(SLIDER_X,675);
}

void FitnessTestScreen::on_invisibleButton_8_pressed()
{
    ui->backgroundLabel->setPixmap(QPixmap(QString(":/images/images/Fitness-Test---06---(Fire-Fighter---Standard).png")));
    showThreeSliders();
}

void FitnessTestScreen::on_invisibleButton_4_pressed()
{
    ui->backgroundLabel->setPixmap(QPixmap(QString(":/images/images/Fitness-Test---06---(Air-Force---Standard).png")));
    showThreeSliders();
}

void FitnessTestScreen::on_invisibleButton_7_pressed()
{
    ui->backgroundLabel->setPixmap(QPixmap(QString(":/images/images/Fitness-Test---06---(Marines---Standard).png")));
    showThreeSliders();
}

void FitnessTestScreen::on_invisibleButton_2_pressed()
{
    ui->backgroundLabel->setPixmap(QPixmap(QString(":/images/images/Fitness-Test---06---(Navy---Standard).png")));
    showThreeSliders();
}

void FitnessTestScreen::on_invisibleButton_3_pressed()
{
    ui->backgroundLabel->setPixmap(QPixmap(QString(":/images/images/Fitness-Test---06---(Army---Standard).png")));
    showThreeSliders();
}

void FitnessTestScreen::on_invisibleButton_fitness_pressed()
{

    ui->backgroundLabel->setPixmap(QPixmap(QString(":/images/images/Fitness-Test---06---(Fitness---Standard).png")));
    showTwoSliders();
}

void FitnessTestScreen::on_invisibleButton_femaleRadio_pressed()
{
    Preferences::gender = FEMALE;

    ui->femaleSelectedLabel->show();
    ui->maleSelectedLabel->hide();
}



void FitnessTestScreen::on_invisibleButton_maleRadio_pressed()
{
    Preferences::gender = MALE;

    ui->maleSelectedLabel->show();
    ui->femaleSelectedLabel->hide();
}

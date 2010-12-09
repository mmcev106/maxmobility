#include "fitnesstestscreen.h"
#include "ui_fitnesstestscreen.h"

#include "mainscreen.h"

static int SLIDER_X = 13;

FitnessTestScreen::FitnessTestScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FitnessTestScreen)
    ,weightSlider(this)
    ,ageSlider(this)
    ,initialSpeedSlider(this, 5, 20)
{
    ui->setupUi(this);
    setAttribute( Qt::WA_DeleteOnClose );

    initialSpeedSlider.move(SLIDER_X,437);
    on_invisibleButton_fitness_pressed();

    ui->backgroundLabel->lower();
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
    MainScreen* w = new MainScreen(0);
    w->show();

    close();
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

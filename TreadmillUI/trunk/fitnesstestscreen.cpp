#include "fitnesstestscreen.h"
#include "ui_fitnesstestscreen.h"

#include "mainscreen.h"

FitnessTestScreen::FitnessTestScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FitnessTestScreen)
    ,weightSlider(this)
    ,ageSlider(this)
    ,timeSlider(this)
{
    ui->setupUi(this);
    setAttribute( Qt::WA_DeleteOnClose );

    weightSlider.move(45,434);
    ageSlider.move(45,551);
    timeSlider.move(45,668);

    hideAllRadioButtonSelectedImages();
    ui->fitnessSelectedLabel->show();

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

void FitnessTestScreen::hideAllRadioButtonSelectedImages(){
    for( int i=0; i < children().size();i++){
        QObject* child = children().at(i);


        if(child->objectName().endsWith("SelectedLabel")){
            QWidget* childWidget = (QWidget*)child;
            childWidget->hide();
        }
    }
}

void FitnessTestScreen::on_invisibleButton_pressed()
{
    hideAllRadioButtonSelectedImages();
    ui->fitnessSelectedLabel->show();
}

void FitnessTestScreen::on_invisibleButton_8_pressed()
{
    hideAllRadioButtonSelectedImages();
    ui->fireSelectedLabel->show();
}

void FitnessTestScreen::on_invisibleButton_4_pressed()
{
    hideAllRadioButtonSelectedImages();
    ui->airSelectedLabel->show();
}

void FitnessTestScreen::on_invisibleButton_7_pressed()
{
    hideAllRadioButtonSelectedImages();
    ui->marinesSelectedLabel->show();
}

void FitnessTestScreen::on_invisibleButton_2_pressed()
{
    hideAllRadioButtonSelectedImages();
    ui->navySelectedLabel->show();
}

void FitnessTestScreen::on_invisibleButton_3_pressed()
{
    hideAllRadioButtonSelectedImages();
    ui->armySelectedLabel->show();
}

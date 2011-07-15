#include "fitnesstestscreen.h"
#include "ui_fitnesstestscreen.h"

#include <QMessageBox>
#include <QDebug>

#include "mainscreen.h"
#include "preferences.h"
#include "screens.h"

static int SLIDER_X = 13;

FitnessTestScreen::FitnessTestScreen(QWidget *parent) :
    AbstractScreen(parent),
    ui(new Ui::FitnessTestScreen)
    ,weightSlider(this)
    ,ageSlider(this)
    ,initialSpeedSlider(this)
    ,fitnessPixmap(":/images/images/Fitness-Test---06---(Fitness---Standard).png")
    ,fireFighterPixmap(":/images/images/Fitness-Test---06---(Fire-Fighter---Standard).png")
    ,airForcePixmap(":/images/images/Fitness-Test---06---(Air-Force---Standard).png")
    ,marinesPixmap(":/images/images/Fitness-Test---06---(Marines---Standard).png")
    ,navyPixmap(":/images/images/Fitness-Test---06---(Navy---Standard).png")
    ,armyPixmap(":/images/images/Fitness-Test---06---(Army---Standard).png")
    ,backgroundPixmap(NULL)
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

    initialSpeedSlider.setValue(6.0);
}

FitnessTestScreen::~FitnessTestScreen()
{
    delete ui;
}

void FitnessTestScreen::on_invisibleButton_5_pressed()
{
    close();
}

void FitnessTestScreen::on_startButton_pressed()
{
    Workout* workout = NULL;

    if(backgroundPixmap == &fitnessPixmap){ //FALSE &&
        workout = Workout::createFitnessWorkout(ageSlider.value, weightSlider.value, Preferences::gender);
        workout->visualization = SCORE_VISUALIZATION;
        workout->scoreTitle = "Fitness Workout";
        workout->scoreResults = "Error Displaying Text";
    }
    else if(backgroundPixmap == &fireFighterPixmap){
        workout = Workout::createFireFighterWorkout( ageSlider.value, weightSlider.value, Preferences::gender);
        workout->visualization = SCORE_VISUALIZATION;
        workout->scoreTitle = "Firefighter Workout";
        workout->scoreResults = "Error Displaying Text";
    }
    else if(backgroundPixmap == &airForcePixmap){
        workout = Workout::createAirForceWorkout(initialSpeedSlider.value, ageSlider.value, weightSlider.value, Preferences::gender);
    }
    else if(backgroundPixmap == &marinesPixmap){
        workout = Workout::createMarinesWorkout(initialSpeedSlider.value, ageSlider.value, weightSlider.value, Preferences::gender);
    }
    else if(backgroundPixmap == &navyPixmap){
        workout = Workout::createNavyWorkout(initialSpeedSlider.value, ageSlider.value, weightSlider.value, Preferences::gender);
    }
    else if(backgroundPixmap == &armyPixmap){
        workout = Workout::createArmyWorkout(initialSpeedSlider.value, ageSlider.value, weightSlider.value, Preferences::gender);
    }
    else{
        qDebug() << "An unknown fitness background was selected";
        return;
    }

    MainScreen::getMainScreen()->startWorkout(workout);
    close();
}

void FitnessTestScreen::showTwoSliders(){

    ui->backgroundLabel->setPixmap(*backgroundPixmap);

    initialSpeedSlider.hide();

    ageSlider.move(SLIDER_X,479);
    weightSlider.move(SLIDER_X,598);
}

void FitnessTestScreen::showThreeSliders(){

    ui->backgroundLabel->setPixmap(*backgroundPixmap);

    initialSpeedSlider.show();

    ageSlider.move(SLIDER_X,556);
    weightSlider.move(SLIDER_X,675);
}

void FitnessTestScreen::on_invisibleButton_8_pressed()
{
    backgroundPixmap = &fireFighterPixmap;
    showTwoSliders();
}

void FitnessTestScreen::on_invisibleButton_4_pressed()
{
    backgroundPixmap = &airForcePixmap;
    showThreeSliders();
}

void FitnessTestScreen::on_invisibleButton_7_pressed()
{
    backgroundPixmap = &marinesPixmap;
    showThreeSliders();
}

void FitnessTestScreen::on_invisibleButton_2_pressed()
{
    backgroundPixmap = &navyPixmap;
    showThreeSliders();
}

void FitnessTestScreen::on_invisibleButton_3_pressed()
{
    backgroundPixmap = &armyPixmap;
    showThreeSliders();
}

void FitnessTestScreen::on_invisibleButton_fitness_pressed()
{

    backgroundPixmap = &fitnessPixmap;
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

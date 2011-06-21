#include "newworkoutscreen.h"
#include "ui_newworkoutscreen.h"
#include "mainscreen.h"
#include "preferences.h"
#include "screens.h"
#include "usbwarningscreen.h"
#include "changespeedstep.h"
#include "changegradestep.h"

#include <QDir>

NewWorkoutScreen::NewWorkoutScreen(QWidget *parent) :
    AbstractScreen(parent),
    ui(new Ui::NewWorkoutScreen)
    ,keyboardWidget(this)
    ,speedSlider(this)
    ,gradeSlider(this)
    ,weightSlider(this)
{
    ui->setupUi(this);

    keyboardWidget.move(157,45);
    speedSlider.move(122, 493);
    gradeSlider.move(122, 585);
    weightSlider.move(122, 677);

    ui->backgroundLabel->lower();
}

NewWorkoutScreen::~NewWorkoutScreen()
{
    delete ui;
}

void NewWorkoutScreen::on_invisibleButton_7_pressed()
{
    close();
}

void NewWorkoutScreen::on_invisibleButton_6_pressed()
{
    QString workoutName = keyboardWidget.text();

    if( workoutName.length() > 0){

        Workout* workout = new Workout(workoutName, weightSlider.value);
        workout->steps->append(new ChangeSpeedStep(speedSlider.value));
        workout->steps->append(new ChangeGradeStep(gradeSlider.value));

        MainScreen::getMainScreen()->recordWorkout(workout);
        close();
    }
}

void NewWorkoutScreen::on_invisibleButton_7_clicked()
{
    close();
}

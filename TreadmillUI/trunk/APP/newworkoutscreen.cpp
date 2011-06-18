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
{
    ui->setupUi(this);

    keyboardWidget.move(157,148);
    speedSlider.move(122, 585);
    gradeSlider.move(122, 677);

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
        QMessageBox::critical(this, "", "Using a weight of 0.  We need to add a way of detecting the user's weight.");

        Workout* workout = new Workout(workoutName, 0);
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

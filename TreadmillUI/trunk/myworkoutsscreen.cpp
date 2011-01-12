#include "myworkoutsscreen.h"
#include "ui_myworkoutsscreen.h"
#include "newworkoutscreen.h"

MyWorkoutsScreen::MyWorkoutsScreen(QWidget *parent) :
    AbstractScreen(parent),
    ui(new Ui::MyWorkoutsScreen)
{
    ui->setupUi(this);
}

MyWorkoutsScreen::~MyWorkoutsScreen()
{
    delete ui;
}

void MyWorkoutsScreen::on_invisibleButton_6_pressed()
{
    (new NewWorkoutScreen())->show();
}

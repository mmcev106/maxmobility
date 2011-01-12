#include "newworkoutscreen.h"
#include "ui_newworkoutscreen.h"

NewWorkoutScreen::NewWorkoutScreen(QWidget *parent) :
    AbstractScreen(parent),
    ui(new Ui::NewWorkoutScreen)
    ,keyboardWidget(this)
{
    ui->setupUi(this);

    keyboardWidget.move(157,148);

    ui->backgroundLabel->lower();
}

NewWorkoutScreen::~NewWorkoutScreen()
{
    delete ui;
}

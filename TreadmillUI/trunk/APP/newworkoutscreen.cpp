#include "newworkoutscreen.h"
#include "ui_newworkoutscreen.h"
#include "mainscreen.h"
#include "preferences.h"

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
    QDir::current().mkdir(WORKOUTS);

    if( keyboardWidget.text().length() > 0){

        QString filename(WORKOUTS + "/" + keyboardWidget.text());
        QFile* workout = new QFile(filename);

        while(workout->exists()){
            delete workout;
            filename = filename.append(" (2)");
            workout = new QFile(filename);
        }

        workout->open(QFile::ReadWrite);
        workout->close();
        delete workout;

        (new MainScreen())->show();
        close();
    }
}

void NewWorkoutScreen::on_invisibleButton_7_clicked()
{
    close();
}

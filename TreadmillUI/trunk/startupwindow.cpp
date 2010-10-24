#include "startupwindow.h"
#include "ui_startupwindow.h"

#include "exercise_hills.h"
#include "videotest.h"

StartupWindow::StartupWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartupWindow)
{
    ui->setupUi(this);
}

StartupWindow::~StartupWindow()
{
    delete ui;
}

void StartupWindow::on_exerciseButton_clicked()
{
    //hide();

//    exercise_hills *window = new exercise_hills();
//    window->show();

}

void StartupWindow::on_exerciseButton_2_clicked()
{

    VideoTest *window = new VideoTest();
    window->show();

}


void showMainScreen(QString action){
    qDebug() << action;
}

void StartupWindow::on_invisibleButton_pressed()
{
        showMainScreen("walk");
}



void StartupWindow::on_invisibleButton_2_pressed()
{
    showMainScreen("fast");
}

void StartupWindow::on_invisibleButton_3_pressed()
{
    showMainScreen("jog");
}

void StartupWindow::on_invisibleButton_4_pressed()
{
    showMainScreen("run");
}

void StartupWindow::on_invisibleButton_5_pressed()
{
    showMainScreen("hill");
}

void StartupWindow::on_invisibleButton_6_pressed()
{
    showMainScreen("steep");
}

void StartupWindow::on_invisibleButton_7_pressed()
{
    showMainScreen("HR Control");
}

void StartupWindow::on_invisibleButton_8_pressed()
{
    showMainScreen("Interval Training");
}

void StartupWindow::on_invisibleButton_10_pressed()
{
    showMainScreen("Fat Burn");
}

void StartupWindow::on_invisibleButton_9_pressed()
{
    showMainScreen("Fitness Tests");
}

void StartupWindow::on_invisibleButton_14_pressed()
{
    showMainScreen("USB");
}

void StartupWindow::on_invisibleButton_11_pressed()
{
    showMainScreen("Workouts");
}

void StartupWindow::on_invisibleButton_12_pressed()
{
    showMainScreen("History");
}

void StartupWindow::on_invisibleButton_13_pressed()
{
    showMainScreen("Help");
}

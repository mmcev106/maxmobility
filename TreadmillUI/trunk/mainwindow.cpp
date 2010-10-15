#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "exercise_hills.h"
#include "videotest.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    on_exerciseButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exerciseButton_clicked()
{
    //hide();

    exercise_hills *window = new exercise_hills();
    window->show();

}

void MainWindow::on_exerciseButton_2_clicked()
{

    VideoTest *window = new VideoTest();
    window->show();

}

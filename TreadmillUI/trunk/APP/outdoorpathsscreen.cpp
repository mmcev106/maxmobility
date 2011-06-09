#include "outdoorpathsscreen.h"
#include "ui_outdoorpathsscreen.h"

OutdoorPathsScreen::OutdoorPathsScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutdoorPathsScreen)
    ,timeSliderWidget(this)
    ,intensitySliderWidget(this)
    ,weightSliderWidget(this)
{
    ui->setupUi(this);

    int x = 10;
    int y = 422;
    int dy = 119;
    timeSliderWidget.move(x, y);
    y += dy;
    intensitySliderWidget.move(x, y);
    y += dy;
    weightSliderWidget.move(x, y);

    ui->backgroundLabel->lower();

    on_woodedButton_pressed();
}

OutdoorPathsScreen::~OutdoorPathsScreen()
{
    delete ui;
}

void OutdoorPathsScreen::on_woodedButton_pressed(){
    hideAllBorders();
    ui->woodedBorder->show();
}

void OutdoorPathsScreen::on_deerButton_pressed(){
    hideAllBorders();
    ui->deerBorder->show();
}

void OutdoorPathsScreen::on_lakeButton_pressed(){
    hideAllBorders();
    ui->lakeBorder->show();
}

void OutdoorPathsScreen::on_cityButton_pressed(){
    hideAllBorders();
    ui->cityBorder->show();
}

void OutdoorPathsScreen::hideAllBorders(){
    ui->woodedBorder->hide();
    ui->deerBorder->hide();
    ui->lakeBorder->hide();
    ui->cityBorder->hide();
}

void OutdoorPathsScreen::on_closeButton_pressed(){
    close();
}

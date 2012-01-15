#include "trailselectionwidget.h"
#include "ui_trailselectionwidget.h"
#include "mainscreen.h"
#include "utils.h"
#include <QPixmap>

TrailSelectionWidget::TrailSelectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrailSelectionWidget)
{
    ui->setupUi(this);
    ui->backgroundLabel->lower();
    ui->blackBackgroundLabel->lower();
}

TrailSelectionWidget::~TrailSelectionWidget()
{
    delete ui;
}

void TrailSelectionWidget::on_radnor_invisibleButton_pressed()
{
    MainScreen::getMainScreen()->playVideo("/videos/trails/radnor.avi");
}

void TrailSelectionWidget::on_couchville_invisibleButton_pressed()
{
    MainScreen::getMainScreen()->playVideo("/videos/trails/lake.avi");
}
void TrailSelectionWidget::on_deer_invisibleButton_pressed()
{
    MainScreen::getMainScreen()->playVideo("/videos/trails/deer.avi");
}

void TrailSelectionWidget::on_nashville_invisibleButton_pressed()
{
    MainScreen::getMainScreen()->playVideo("/videos/trails/downtown.avi");
}

#include "tranquilselectionwidget.h"
#include "ui_tranquilselectionwidget.h"
#include "mainscreen.h"
#include <QPixmap>

TranquilSelectionWidget::TranquilSelectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TranquilSelectionWidget)
{
    ui->setupUi(this);
    ui->backgroundLabel->lower();
    ui->blackBackgroundLabel->lower();
}

TranquilSelectionWidget::~TranquilSelectionWidget()
{
    delete ui;
}

void TranquilSelectionWidget::on_ducks_invisibleButton_pressed()
{
    MainScreen::getMainScreen()->ShowWidget(VIDEO_VISUALIZATION,"/videos/tranquil/ducks.avi");
}

void TranquilSelectionWidget::on_fish_invisibleButton_pressed()
{
    MainScreen::getMainScreen()->ShowWidget(VIDEO_VISUALIZATION,"/videos/tranquil/fish.avi");
}
void TranquilSelectionWidget::on_ocean_invisibleButton_pressed()
{
    MainScreen::getMainScreen()->ShowWidget(VIDEO_VISUALIZATION,"/videos/tranquil/ocean.avi");
}

void TranquilSelectionWidget::on_waterfall_invisibleButton_pressed()
{
    MainScreen::getMainScreen()->ShowWidget(VIDEO_VISUALIZATION,"/videos/tranquil/waterfall.avi");
}

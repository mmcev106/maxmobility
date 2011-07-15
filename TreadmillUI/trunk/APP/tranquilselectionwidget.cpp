#include "tranquilselectionwidget.h"
#include "ui_tranquilselectionwidget.h"
#include "mainscreen.h"
#include "utils.h"
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
    MainScreen::getMainScreen()->playVideo("/videos/tranquil/ducks.avi");
}

void TranquilSelectionWidget::on_fish_invisibleButton_pressed()
{
    MainScreen::getMainScreen()->playVideo("/videos/tranquil/fish.avi");
}
void TranquilSelectionWidget::on_ocean_invisibleButton_pressed()
{
    MainScreen::getMainScreen()->playVideo("/videos/tranquil/sea.avi");
}

void TranquilSelectionWidget::on_waterfall_invisibleButton_pressed()
{
    MainScreen::getMainScreen()->playVideo("/videos/tranquil/waterfall.avi");
}

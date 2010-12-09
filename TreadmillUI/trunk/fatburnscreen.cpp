#include "fatburnscreen.h"
#include "ui_fatburnscreen.h"

#include "mainscreen.h"

FatBurnScreen::FatBurnScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FatBurnScreen)
    ,timeSlider(this)
    ,intensitySlider(this, 1, 100)
    ,weightSlider(this)
{
    ui->setupUi(this);
    setAttribute( Qt::WA_DeleteOnClose );

    int x = 14;
    timeSlider.move(x,275);
    intensitySlider.move(x,395);
    weightSlider.move(x,514);

    ui->backgroundLabel->lower();
}

FatBurnScreen::~FatBurnScreen()
{
    delete ui;
}

void FatBurnScreen::on_invisibleButton_7_pressed()
{
    close();
}

void FatBurnScreen::on_invisibleButton_6_pressed()
{
    MainScreen* w = new MainScreen(0);
    w->show();

    close();
}

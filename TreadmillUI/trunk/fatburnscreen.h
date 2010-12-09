#ifndef FATBURNSCREEN_H
#define FATBURNSCREEN_H

#include <QWidget>

#include "timesliderwidget.h"
#include "weightsliderwidget.h"
#include "sliderwidget.h"

namespace Ui {
    class FatBurnScreen;
}

class FatBurnScreen : public QWidget
{
    Q_OBJECT

public:
    explicit FatBurnScreen(QWidget *parent = 0);
    ~FatBurnScreen();

private:
    Ui::FatBurnScreen *ui;

    TimeSliderWidget timeSlider;
    SliderWidget intensitySlider;
    WeightSliderWidget weightSlider;


private slots:
    void on_invisibleButton_6_pressed();
    void on_invisibleButton_7_pressed();
};

#endif // FATBURNSCREEN_H

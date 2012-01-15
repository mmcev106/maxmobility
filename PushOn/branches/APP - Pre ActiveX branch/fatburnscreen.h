#ifndef FATBURNSCREEN_H
#define FATBURNSCREEN_H

#include <QWidget>

#include "timesliderwidget.h"
#include "weightsliderwidget.h"
#include "sliderwidget.h"
#include "abstractmultisliderscreen.h"
#include "speedsliderwidget.h"

namespace Ui {
    class FatBurnScreen;
}

class FatBurnScreen : public AbstractMultiSliderScreen
{
    Q_OBJECT

public:
    explicit FatBurnScreen(QWidget *parent = 0);
    ~FatBurnScreen();

protected:
    bool event(QEvent *event);

private:
    Ui::FatBurnScreen *ui;

    TimeSliderWidget timeSlider;
    SliderWidget intensitySlider;
    SpeedSliderWidget speedSlider;
    WeightSliderWidget weightSlider;

    void updateHistory();

private slots:
    void on_invisibleButton_6_pressed();
    void on_invisibleButton_7_pressed();
};

#endif // FATBURNSCREEN_H

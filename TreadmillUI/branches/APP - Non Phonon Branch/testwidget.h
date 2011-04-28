#ifndef TESTWIDGT_H
#define TESTWIDGT_H

#include "abstractmultisliderscreen.h"

#include "sliderwidget.h"
#include "weightsliderwidget.h"
#include "agesliderwidget.h"
#include "timesliderwidget.h"
#include "speedsliderwidget.h"
#include "historywidget.h"

namespace Ui {
    class FatBurnScreen;
}

class HeartRateScreen2 : public AbstractMultiSliderScreen
{
    Q_OBJECT

public:
    explicit HeartRateScreen2(QWidget *parent = 0);
    ~HeartRateScreen2();

protected:
    bool event(QEvent *event);

private:
    Ui::FatBurnScreen *ui;
    WeightSliderWidget weightSlider;
    AgeSliderWidget ageSlider;
    TimeSliderWidget timeSlider;
    SpeedSliderWidget speedSlider1;
    SpeedSliderWidget speedSlider2;

    void setConstantGrade();
    void setDynamicGrade();
    void updateHistory();

private slots:
    void on_invisibleButton_5_pressed();
    void on_invisibleButton_6_pressed();
    void on_invisibleButton_4_pressed();
    void on_invisibleButton_3_pressed();
};

#endif // HEARTRATESCREEN_H

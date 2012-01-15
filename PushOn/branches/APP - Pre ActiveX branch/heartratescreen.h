#ifndef HEARTRATESCREEN_H
#define HEARTRATESCREEN_H

#include "abstractmultisliderscreen.h"

#include "sliderwidget.h"
#include "weightsliderwidget.h"
#include "agesliderwidget.h"
#include "timesliderwidget.h"
#include "speedsliderwidget.h"
#include "historywidget.h"

namespace Ui {
    class HeartRateScreen;
}

class HeartRateScreen : public AbstractMultiSliderScreen
{
    Q_OBJECT

public:
    explicit HeartRateScreen(QWidget *parent = 0);
    ~HeartRateScreen();

protected:
    bool event(QEvent *event);

private:
    Ui::HeartRateScreen *ui;
    WeightSliderWidget weightSlider;
    AgeSliderWidget ageSlider;
    TimeSliderWidget timeSlider;
    SliderWidget lowPercentageSlider;
    SliderWidget highPercentageSlider;

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

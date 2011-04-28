#ifndef INTERVALSCREEN_H
#define INTERVALSCREEN_H

#include "abstractmultisliderscreen.h"

#include "timesliderwidget.h"
#include "gradesliderwidget.h"
#include "speedsliderwidget.h"
#include "agesliderwidget.h"
#include "weightsliderwidget.h"
#include "historywidget.h"

namespace Ui {
    class IntervalScreen;
}

class IntervalScreen : public AbstractMultiSliderScreen
{
    Q_OBJECT

public:
    explicit IntervalScreen(QWidget *parent = 0);
    ~IntervalScreen();

protected:
    bool event(QEvent *event);

private:
    Ui::IntervalScreen *ui;

    TimeSliderWidget timeSlider;
    GradeSliderWidget lowGradeSlider;
    GradeSliderWidget highGradeSlider;
    SpeedSliderWidget lowSpeedSlider;
    SpeedSliderWidget highSpeedSlider;
    AgeSliderWidget ageSlider;
    WeightSliderWidget weightSlider;

    void updateHistoryFromSpeeds();
    void updateHistoryFromGrades();

private slots:
    void on_invisibleButton_hills_3_pressed();
    void on_invisibleButton_hills_2_pressed();
    void on_invisibleButton_4_pressed();
    void on_invisibleButton_hills_pressed();
};

#endif // INTERVALSCREEN_H

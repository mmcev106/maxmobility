#ifndef HEARTRATESCREEN_H
#define HEARTRATESCREEN_H

#include <QWidget>

#include "sliderwidget.h"
#include "weightsliderwidget.h"
#include "agesliderwidget.h"
#include "timesliderwidget.h"
#include "historywidget.h"

namespace Ui {
    class HeartRateScreen;
}

class HeartRateScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HeartRateScreen(QWidget *parent = 0);
    ~HeartRateScreen();

private:
    Ui::HeartRateScreen *ui;
    WeightSliderWidget weightSlider;
    AgeSliderWidget ageSlider;
    TimeSliderWidget timeSlider;
    SliderWidget lowSpeedSlider;
    SliderWidget highSpeedSlider;

    static const int HISTORY_LENGTH = 12;
    HistoryWidget gradeHistoryWidget;

    void setConstantGrade();
    void setDynamicGrade();

private slots:
    void on_invisibleButton_5_pressed();
    void on_invisibleButton_6_pressed();
    void on_invisibleButton_4_pressed();
    void on_invisibleButton_3_pressed();
};

#endif // HEARTRATESCREEN_H

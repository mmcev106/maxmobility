#ifndef FITNESSTESTSCREEN_H
#define FITNESSTESTSCREEN_H

#include <QWidget>
#include <weightsliderwidget.h>
#include "agesliderwidget.h"
#include "timesliderwidget.h"
#include <sliderwidget.h>

namespace Ui {
    class FitnessTestScreen;
}

class FitnessTestScreen : public QWidget
{
    Q_OBJECT

public:
    explicit FitnessTestScreen(QWidget *parent = 0);
    ~FitnessTestScreen();

private:
    Ui::FitnessTestScreen *ui;
    WeightSliderWidget weightSlider;
    AgeSliderWidget ageSlider;
    TimeSliderWidget timeSlider;

    void hideAllRadioButtonSelectedImages();

private slots:
    void on_invisibleButton_3_pressed();
    void on_invisibleButton_2_pressed();
    void on_invisibleButton_7_pressed();
    void on_invisibleButton_4_pressed();
    void on_invisibleButton_8_pressed();
    void on_invisibleButton_pressed();
    void on_invisibleButton_6_pressed();
    void on_invisibleButton_5_pressed();
};

#endif // FITNESSTESTSCREEN_H

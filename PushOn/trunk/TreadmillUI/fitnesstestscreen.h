#ifndef FITNESSTESTSCREEN_H
#define FITNESSTESTSCREEN_H

#include "abstractscreen.h"
#include <weightsliderwidget.h>
#include "agesliderwidget.h"
#include "timesliderwidget.h"
#include "speedsliderwidget.h"
#include "sliderwidget.h"

namespace Ui {
    class FitnessTestScreen;
}

class FitnessTestScreen : public AbstractScreen
{
    Q_OBJECT

public:
    explicit FitnessTestScreen(QWidget *parent = 0);
    ~FitnessTestScreen();

private:
    Ui::FitnessTestScreen *ui;

    WeightSliderWidget weightSlider;
    AgeSliderWidget ageSlider;
    SpeedSliderWidget initialSpeedSlider;

    void showTwoSliders();
    void showThreeSliders();

    QPixmap fitnessPixmap;
    QPixmap fireFighterPixmap;
    QPixmap airForcePixmap;
    QPixmap marinesPixmap;
    QPixmap navyPixmap;
    QPixmap armyPixmap;

    QPixmap* backgroundPixmap;

private slots:
    void on_invisibleButton_maleRadio_pressed();
    void on_invisibleButton_femaleRadio_pressed();
    void on_invisibleButton_fitness_pressed();
    void on_invisibleButton_3_pressed();
    void on_invisibleButton_2_pressed();
    void on_invisibleButton_7_pressed();
    void on_invisibleButton_4_pressed();
    void on_invisibleButton_8_pressed();
    void on_startButton_pressed();
    void on_invisibleButton_5_pressed();
};

#endif // FITNESSTESTSCREEN_H
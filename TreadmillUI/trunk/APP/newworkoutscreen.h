#ifndef NEWWORKOUTSCREEN_H
#define NEWWORKOUTSCREEN_H

#include <QWidget>
#include "abstractscreen.h"
#include "keyboardwidget.h"
#include "gradesliderwidget.h"
#include "speedsliderwidget.h"
#include "weightsliderwidget.h"

namespace Ui {
    class NewWorkoutScreen;
}

class NewWorkoutScreen : public AbstractScreen
{
    Q_OBJECT

public:
    explicit NewWorkoutScreen(QWidget *parent = 0);
    ~NewWorkoutScreen();

private:
    Ui::NewWorkoutScreen *ui;
    KeyboardWidget keyboardWidget;
    SpeedSliderWidget speedSlider;
    GradeSliderWidget gradeSlider;
    WeightSliderWidget weightSlider;

private slots:
    void on_invisibleButton_7_clicked();
    void on_invisibleButton_6_pressed();
    void on_invisibleButton_7_pressed();
};

#endif // NEWWORKOUTSCREEN_H

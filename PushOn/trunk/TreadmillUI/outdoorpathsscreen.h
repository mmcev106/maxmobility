#ifndef OUTDOORPATHSSCREEN_H
#define OUTDOORPATHSSCREEN_H

#include <QWidget>
#include "timesliderwidget.h"
#include "intensitysliderwidget.h"
#include "weightsliderwidget.h"
#include "historywidget.h"
#include "abstractscreen.h"
#include "workout.h"

namespace Ui {
    class OutdoorPathsScreen;
}

class OutdoorPathsScreen : public AbstractScreen
{
    Q_OBJECT

public:
    explicit OutdoorPathsScreen(QWidget *parent = 0);
    ~OutdoorPathsScreen();

private:
    Ui::OutdoorPathsScreen *ui;

    TimeSliderWidget timeSliderWidget;
    IntensitySliderWidget intensitySliderWidget;
    WeightSliderWidget weightSliderWidget;

    int* history;
    HistoryWidget historyWidget;

    void hideAllBorders();
    void updateHistoryFromIntensity();
    const char* selected_Item(void);
    Workout* createTrailWorkout(QString videoName);

protected:
    bool event(QEvent *event);

private slots:
    void on_woodedButton_pressed();
    void on_deerButton_pressed();
    void on_lakeButton_pressed();
    void on_cityButton_pressed();
    void on_closeButton_pressed();
    void on_startButton_pressed();
};

#endif // OUTDOORPATHSSCREEN_H

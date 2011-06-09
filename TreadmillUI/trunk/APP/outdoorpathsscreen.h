#ifndef OUTDOORPATHSSCREEN_H
#define OUTDOORPATHSSCREEN_H

#include <QWidget>
#include "timesliderwidget.h"
#include "intensitysliderwidget.h"
#include "weightsliderwidget.h"

namespace Ui {
    class OutdoorPathsScreen;
}

class OutdoorPathsScreen : public QWidget
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

    void hideAllBorders();

private slots:
    void on_woodedButton_pressed();
    void on_deerButton_pressed();
    void on_lakeButton_pressed();
    void on_cityButton_pressed();
    void on_closeButton_pressed();
};

#endif // OUTDOORPATHSSCREEN_H

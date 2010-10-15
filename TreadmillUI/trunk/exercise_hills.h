#ifndef EXERCISE_HILLS_H
#define EXERCISE_HILLS_H

#include <QWidget>

#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_data.h>
#include <qwt_text.h>
#include <qwt_math.h>
#include <math.h>
#include <QColor>
#include <QTimer>

namespace Ui {
    class exercise_hills;
}

class exercise_hills : public QWidget
{
    Q_OBJECT

public:
    explicit exercise_hills(QWidget *parent = 0);
    ~exercise_hills();

private:
    Ui::exercise_hills *ui;
    QwtPlot plot;
    QTimer timer;
    double* xValues;
    double* speedYValues;
    double* gradeYValues;
    QwtPlotCurve *speedCurve;
    QwtPlotCurve *gradeCurve;
    int getScaledRateOfChange();

private slots:
    void on_pushButton_6_released();
    void on_pushButton_6_pressed();
    void on_pushButton_5_released();
    void on_pushButton_5_pressed();
    void on_pushButton_4_released();
    void on_pushButton_4_pressed();
    void on_pushButton_3_released();
    void on_pushButton_3_pressed();
    void updateGraph();
};

#endif // EXERCISE_HILLS_H

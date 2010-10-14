#include "exercise_hills.h"
#include "ui_exercise_hills.h"
#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_data.h>
#include <qwt_text.h>
#include <qwt_math.h>
#include <qwt_scale_engine.h>
#include <math.h>
#include <QColor>
#include <QDebug>

static int X_AXIS = 2;
static int Y_AXIS = 0;
static int DATA_LENGTH = 100;
static int RATE_OF_CHANGE = 50;

int speedRate = 0;
int gradeRate = 0;
bool speedUpPressed = false;
bool speedDownPressed = false;
bool gradeUpPressed = false;
bool gradeDownPressed = false;

class Plot : public QwtPlot
{
    public:
        Plot();

};


Plot::Plot()
{

}

exercise_hills::exercise_hills(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::exercise_hills),
    plot(new Plot::Plot()),
    timer(new QTimer(this)),
    speedCurve(new QwtPlotCurve()),
    gradeCurve(new QwtPlotCurve()),
    xValues(new double[DATA_LENGTH]),
    speedYValues(new double[DATA_LENGTH]),
    gradeYValues(new double[DATA_LENGTH])
{
    ui->setupUi(this);



    gradeCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
    QColor green = QColor(34, 167, 45);
    QPen greenPen = QPen(green);
    greenPen.setWidth(4);
    gradeCurve->setPen(greenPen);
    gradeCurve->attach(&plot);

    speedCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
    QPen redPen = QPen(Qt::red);
    redPen.setWidth(2);
    speedCurve->setPen(redPen);
    speedCurve->attach(&plot);

    for(int i=0;i<DATA_LENGTH;i++){
        xValues[i] = i;
        speedYValues[i] = 0;
        gradeYValues[i] = 0;
    }

    speedCurve->setRawData(xValues, speedYValues, DATA_LENGTH);
    gradeCurve->setRawData(xValues, gradeYValues, DATA_LENGTH);

    plot.setParent(this);

    plot.setStyleSheet("background-color: white");
    plot.enableAxis(X_AXIS, false);
    plot.enableAxis(Y_AXIS, false);

    int margin = RATE_OF_CHANGE/2;
    plot.axisScaleEngine(Y_AXIS)->setMargins(margin, margin);

    plot.resize(431,141);
    plot.move(300,600);
    plot.show();

    timer.setSingleShot(false);
    timer.setInterval(100);
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGraph()));
    timer.start();
}

exercise_hills::~exercise_hills()
{
    delete ui;
    delete speedCurve;
    delete gradeCurve;
    delete xValues;
    delete speedYValues;
    delete gradeYValues;
}

void progress(double * d, int length){

    for(int i=0;i<length-1;i++){
        d[i] = d[i+1];
    }
}

int exercise_hills::getScaledRateOfChange(){

    int min = speedYValues[0];
    int max = speedYValues[0];

    for(int i=0;i<DATA_LENGTH;i++){

        if(speedYValues[i] < min){
            min = speedYValues[i];
        }

        if(speedYValues[i] > max){
            max = speedYValues[i];
        }

        if(gradeYValues[i] < min){
            min = gradeYValues[i];
        }

        if(gradeYValues[i] > max){
            max = gradeYValues[i];
        }
    }

    int rate = (max - min)/RATE_OF_CHANGE;

    if(rate == 0){
        return 1;
    }
    else{
        qDebug() << "rate of change: " << rate;
        return rate;
    }
}

void exercise_hills::updateGraph(){

    progress(speedYValues, DATA_LENGTH);
    progress(gradeYValues, DATA_LENGTH);


    int rateOfChange = getScaledRateOfChange();

    if(speedUpPressed){
        speedRate += rateOfChange;
    }
    else if (speedDownPressed){
        speedRate -= rateOfChange;
    }
    else if( speedRate < 0){
        speedRate += rateOfChange;

        if( speedRate > 0 ){
            speedRate = 0;
        }
    }
    else if( speedRate > 0){

        speedRate -= rateOfChange;

        if(speedRate < 0){
            speedRate = 0;
        }
    }

    if (gradeUpPressed){
        gradeRate += rateOfChange;
    }
    else if(gradeDownPressed){
        gradeRate -= rateOfChange;
    }
    else if (gradeRate < 0){

        gradeRate += rateOfChange;

        if(gradeRate > 0){
            gradeRate = 0;
        }
    }
    else if(gradeRate > 0){
        gradeRate -= rateOfChange;

        if(gradeRate < 0){
            gradeRate = 0;
        }
    }

    qDebug() << "speed rate: " << speedRate;
    qDebug() << "grade rate: " << gradeRate;

    speedYValues[DATA_LENGTH-1] += speedRate;
    gradeYValues[DATA_LENGTH-1] += gradeRate;

    speedCurve->setData(xValues, speedYValues, DATA_LENGTH);
    gradeCurve->setData(xValues, gradeYValues, DATA_LENGTH);

    plot.replot();
}

void exercise_hills::on_pushButton_3_pressed()
{
    speedUpPressed = true;
}

void exercise_hills::on_pushButton_3_released()
{
    speedUpPressed = false;
}

void exercise_hills::on_pushButton_4_pressed()
{
    speedDownPressed = true;
}

void exercise_hills::on_pushButton_4_released()
{
    speedDownPressed = false;
}

void exercise_hills::on_pushButton_5_pressed()
{
    qDebug() << "down";
    gradeUpPressed = true;
}

void exercise_hills::on_pushButton_5_released()
{
    qDebug() << "up";
    gradeUpPressed = false;
}

void exercise_hills::on_pushButton_6_pressed()
{
    gradeDownPressed = true;
}

void exercise_hills::on_pushButton_6_released()
{
    gradeDownPressed = false;
}

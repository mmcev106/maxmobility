#include "sliderwidget.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QFont>

#include "pointerevent.h"
#include <QApplication>

static int LEFT_ARROW_WIDTH = 38;
static int SLIDER_MIDDLE_WIDTH = 93;
static int RIGHT_ARROW_WIDTH = 38;

static int HIDE_ARROW_THRESHOLD = 70;

static QPixmap *bothArrowsPixmap = 0;
static QPixmap *leftArrowPixmap = 0;
static QPixmap *rightArrowPixmap = 0;

static QPixmap* getBothArrowsPixmap(){
    if(bothArrowsPixmap == 0){
        bothArrowsPixmap = new QPixmap(":/images/images/slider_both_arrows.png");
    }

    return bothArrowsPixmap;
}

static QPixmap* getLeftArrowPixmap(){
    if(leftArrowPixmap == 0){
        leftArrowPixmap = new QPixmap(":/images/images/slider_left_arrow.png");
    }

    return leftArrowPixmap;
}

static QPixmap* getRightArrowPixmap(){
    if(rightArrowPixmap == 0){
        rightArrowPixmap = new QPixmap(":/images/images/slider_right_arrow.png");
    }

    return rightArrowPixmap;
}


SliderWidget::SliderWidget(QWidget *parent, double min, double max) :
    QWidget(parent)
{
    this->min = min;
    this->max = max;

    this->step = 1;

    this->value = min;

    setFixedSize(540,57);
    show();

    minXValue = LEFT_ARROW_WIDTH;
    maxXValue = width() - getRightArrowPixmap()->width();
    xRange = maxXValue - minXValue;
    range = max - min;
}

int SliderWidget::getSliderMiddleX(){

    int disanceFromMin = value - min;
//    qDebug() << "disanceFromMin: " << disanceFromMin;
//    qDebug() << "range: " << range;
    double percent = ((double)disanceFromMin)/range;
//    qDebug() << "percent: " << percent;

    return (int) (percent * xRange + minXValue );
}

void SliderWidget::paintEvent(QPaintEvent *){

    QPainter painter (this);

    int sliderMiddleX = getSliderMiddleX();

    if( sliderMiddleX < HIDE_ARROW_THRESHOLD ){
        painter.drawPixmap( sliderMiddleX, 0, *getRightArrowPixmap());
    }
    else if ( sliderMiddleX + SLIDER_MIDDLE_WIDTH > width() - HIDE_ARROW_THRESHOLD ){
        painter.drawPixmap( sliderMiddleX - LEFT_ARROW_WIDTH, 0, *getLeftArrowPixmap());
    }
    else{
        painter.drawPixmap( sliderMiddleX - LEFT_ARROW_WIDTH, 0, *getBothArrowsPixmap());
    }

    painter.setFont(QFont("Tamworth Gothic", 18));
    QString text = QString("%1").arg(value);
    int textWidth = painter.fontMetrics().width(text);

    int textX = sliderMiddleX + SLIDER_MIDDLE_WIDTH/2;
    textX -= textWidth/2;

    painter.drawText(textX, 33, text);
}

void SliderWidget::setValue(int value){

    if(value < min){
        value = min;
    }
    else if (value > max){
        value = max;
    }

    this->value = value;
    update();
}

void SliderWidget::setValueFromX(int x){
//    qDebug() << "value from x x: " << x;

    int distanceFromMin = x - minXValue;
    double percent = ((double)distanceFromMin) / xRange;

//    qDebug() << "percent: " << percent;
//    qDebug() << "setting value: " << (int) (percent * range) + min;

    setValue((int) (percent * range) + min);

    PointerEvent* event = new PointerEvent(this);
    QApplication::postEvent(parent(), event);
}

void SliderWidget::mouseMoveEvent(QMouseEvent *event){
    setValueFromX(event->x() - touchDistanceFromX);
}

bool SliderWidget::isLeftArrowPressed(QMouseEvent * event, int sliderMiddleX){
    return event->x() >= sliderMiddleX-LEFT_ARROW_WIDTH && event->x() < sliderMiddleX;
}

bool SliderWidget::isRightArrowPressed(QMouseEvent * event, int sliderMiddleX){
    int sliderRightEdge = sliderMiddleX + SLIDER_MIDDLE_WIDTH;
    return event->x() >= sliderRightEdge && event->x() < sliderRightEdge+RIGHT_ARROW_WIDTH;
}

bool SliderWidget::isMiddlePressed(QMouseEvent * event, int sliderMiddleX){
    return  event->x() > sliderMiddleX &&  event->x() < sliderMiddleX+SLIDER_MIDDLE_WIDTH;
}

void SliderWidget::mousePressEvent(QMouseEvent * event){

    int sliderMiddleX = getSliderMiddleX();

    if(isLeftArrowPressed(event, sliderMiddleX)){
        setValue(value - 1);
    }
    else if (isRightArrowPressed(event, sliderMiddleX)){
        setValue(value + 1);
    }
    else if (!isMiddlePressed(event, sliderMiddleX)){
        //The user touched outside of the current slider position.  Move the slider.

        //adjust x so that the user's finger ends up in the middle of the slider
        int x = event->x() - SLIDER_MIDDLE_WIDTH/2;

        qDebug() << "Moving the slider to " << x;

        setValueFromX(x);
    }

    touchDistanceFromX =  event->x() - getSliderMiddleX();
}

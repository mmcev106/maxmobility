#include "sliderwidget.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QFont>

static int NOT_VISIBLE = -9999;

static QPixmap *middlePixmap = 0;
static QPixmap *leftArrowPixmap = 0;
static QPixmap *rightArrowPixmap = 0;

static QPixmap* getMiddlePixmap(){
    if(middlePixmap == 0){
        middlePixmap = new QPixmap(":/images/images/slider_middle.png");
    }

    return middlePixmap;
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


SliderWidget::SliderWidget(QWidget *parent, int min, int max) :
    QWidget(parent)
{
    this->min = min;
    this->max = max;

    this->value = min;

    setFixedSize(540,57);
    show();

    minXValue = getLeftArrowPixmap()->width();
    maxXValue = width() - getRightArrowPixmap()->width() - getMiddlePixmap()->width();
    xRange = maxXValue - minXValue;
    range = max - min;
    leftArrowPosition = NOT_VISIBLE;
    rightArrowPosition = NOT_VISIBLE;

    qDebug() << "test: " << max << "," << min << ",  " << range;
    qDebug() << "range1: " << range;
}

int SliderWidget::getX(){

    int disanceFromMin = value - min;
//    qDebug() << "disanceFromMin: " << disanceFromMin;
//    qDebug() << "range: " << range;
    double percent = ((double)disanceFromMin)/range;
//    qDebug() << "percent: " << percent;

    return (int) (percent * xRange + minXValue );
}

void SliderWidget::paintEvent(QPaintEvent *){

    qDebug() << "range1: " << range;

    QPainter painter (this);

    int x = getX();
    qDebug() << "x: " << x;

    painter.drawPixmap( x, 0, *getMiddlePixmap());

    if(value > min){
        leftArrowPosition = x - getLeftArrowPixmap()->width();
        painter.drawPixmap( leftArrowPosition, 0, *getLeftArrowPixmap());
    }
    else{
        leftArrowPosition = NOT_VISIBLE;
    }

    if (value < max){
        rightArrowPosition = x + getMiddlePixmap()->width();
        painter.drawPixmap( rightArrowPosition, 0, *getRightArrowPixmap());
    }
    else{
        rightArrowPosition = NOT_VISIBLE;
    }

    painter.setFont(QFont("Tamworth Gothic", 18));
    QString text = QString("%1").arg(value);
    int textWidth = painter.fontMetrics().width(text);

    int textX = x + getMiddlePixmap()->width()/2 -1;
    textX -= textWidth/2;

    painter.drawText(textX, 32, text);
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
}

void SliderWidget::mouseMoveEvent(QMouseEvent *event){
    setValueFromX(event->x() - touchDistanceFromX);
}

bool SliderWidget::isLeftArrowPressed(QMouseEvent * event){
    return event->x() >= leftArrowPosition && event->x() < leftArrowPosition + leftArrowPixmap->width();
}

bool SliderWidget::isRightArrowPressed(QMouseEvent * event){
    return event->x() >= rightArrowPosition && event->x() < rightArrowPosition + rightArrowPixmap->width();
}

bool SliderWidget::isMiddlePressed(QMouseEvent * event){
    int x = event->x();
    return x > leftArrowPosition + leftArrowPixmap->width() && x < rightArrowPosition;
}

void SliderWidget::mousePressEvent(QMouseEvent * event){
    qDebug() << "range1: " << range;

    if(isLeftArrowPressed(event)){
        setValue(value - 1);
    }
    else if (isRightArrowPressed(event)){
        setValue(value + 1);
    }
    else if (!isMiddlePressed(event)){
        //The user touched outside of the current slider position.  Move the slider.

        //adjust x so that the user's finger ends up in the middle of the slider
        int x = event->x() - getMiddlePixmap()->width()/2;

        qDebug() << "Moving the slider to " << x;

        setValueFromX(x);
    }

    touchDistanceFromX =  event->x() - getX();
}

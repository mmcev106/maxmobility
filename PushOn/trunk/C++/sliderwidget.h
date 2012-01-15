#ifndef SLIDERWIDGET_H
#define SLIDERWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QDebug>

class SliderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SliderWidget(QWidget *parent = 0, double min=0, double max=0);
    double value;
    double step;
    double min;
    double max;

    void setValue(double);
    double getPercentage();
    void initialize();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent * event);

    static const int DEFAULT_WIDTH = 540;
    static const int DEFAULT_HEIGHT = 57;

    virtual int fontSize();

private:
    int minXValue;
    int maxXValue;
    int xRange;
    int range;

    int touchDistanceFromX;

    void paintEvent(QPaintEvent *);
    int getSliderMiddleX();
    void setValueFromX(int);
    bool isLeftArrowPressed(QMouseEvent*, int);
    bool isRightArrowPressed(QMouseEvent*, int);
    bool isMiddlePressed(QMouseEvent*, int);

signals:

public slots:

};

#endif // SLIDERWIDGET_H

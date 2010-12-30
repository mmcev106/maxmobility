#ifndef SLIDERWIDGET_H
#define SLIDERWIDGET_H

#include <QWidget>
#include <QPixmap>

class SliderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SliderWidget(QWidget *parent = 0, double min=0, double max=0);
    double value;
    double step;

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent * event);

private:
    double min;
    double max;

    int minXValue;
    int maxXValue;
    int xRange;
    int range;

    int touchDistanceFromX;

    void paintEvent(QPaintEvent *);
    int getSliderMiddleX();
    void setValue(int);
    void setValueFromX(int);
    bool isLeftArrowPressed(QMouseEvent*, int);
    bool isRightArrowPressed(QMouseEvent*, int);
    bool isMiddlePressed(QMouseEvent*, int);

signals:

public slots:

};

#endif // SLIDERWIDGET_H

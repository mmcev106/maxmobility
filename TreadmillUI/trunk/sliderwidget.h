#ifndef SLIDERWIDGET_H
#define SLIDERWIDGET_H

#include <QWidget>
#include <QPixmap>

class SliderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SliderWidget(QWidget *parent = 0, int min=0, int max=0);
    int value;

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent * event);

private:
    int min;
    int max;

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

#ifndef SLIDERWIDGET_H
#define SLIDERWIDGET_H

#include <QWidget>
#include <QPixmap>

class SliderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SliderWidget(QWidget *parent = 0, int min=0, int max=0);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent * event);

private:
    int min;
    int max;
    int value;

    int minXValue;
    int maxXValue;
    int xRange;
    int range;

    int leftArrowPosition;
    int rightArrowPosition;

    int touchDistanceFromX;

    void paintEvent(QPaintEvent *);
    int getX();
    void setValue(int);
    void setValueFromX(int);
    bool isLeftArrowPressed(QMouseEvent*);
    bool isRightArrowPressed(QMouseEvent*);
    bool isMiddlePressed(QMouseEvent*);

signals:

public slots:

};

#endif // SLIDERWIDGET_H

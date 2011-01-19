#ifndef RADIOSLIDERWIDGET_H
#define RADIOSLIDERWIDGET_H

#include "sliderwidget.h"

class RadioSliderWidget : public SliderWidget
{
    Q_OBJECT
public:
    explicit RadioSliderWidget(QWidget *parent = 0);

protected:
    int fontSize();

signals:

public slots:

};

#endif // RADIOSLIDERWIDGET_H

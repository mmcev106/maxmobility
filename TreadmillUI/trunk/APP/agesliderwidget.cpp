#include "agesliderwidget.h"

AgeSliderWidget::AgeSliderWidget(QWidget *parent) :
    SliderWidget(parent, 12, 99)
{
    setValue(25);
}

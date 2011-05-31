#include "speedsliderwidget.h"
#include "utils.h"

SpeedSliderWidget::SpeedSliderWidget(QWidget *parent) :
        SliderWidget(parent, 1, (Utils::getMAX_SPEED()/10))
{
}

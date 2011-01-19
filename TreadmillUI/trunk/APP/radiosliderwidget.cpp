#include "radiosliderwidget.h"
#include "QDebug"

static const int RADIO_SLIDER_FONT_SIZE = 16;

RadioSliderWidget::RadioSliderWidget(QWidget *parent) :
    SliderWidget(parent, 87.5, 107.9 )
{
    setFixedWidth(753);
    initialize();
}


int RadioSliderWidget::fontSize(){
    return RADIO_SLIDER_FONT_SIZE;
}

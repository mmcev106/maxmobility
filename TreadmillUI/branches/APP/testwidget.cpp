#include "testwidget.h"
#include "ui_fatburnscreen.h"

#include "mainscreen.h"
#include "pointerevent.h"
#include "screens.h"

HeartRateScreen2::HeartRateScreen2(QWidget *parent) :
    AbstractMultiSliderScreen(parent)
    ,ui(new Ui::FatBurnScreen)
    ,weightSlider(this)
    ,ageSlider(this)
    ,timeSlider(this)
    ,speedSlider1(this)
    ,speedSlider2(this)
{
    ui->setupUi(this);

    timeSlider.move(SLIDER_X,SLIDER1_Y);
    speedSlider1.move(SLIDER_X,SLIDER2_Y);
    speedSlider2.move(SLIDER_X, SLIDER3_Y);

    setConstantGrade();

    //Put the background behind the sliders
    ui->backgroundLabel->lower();
}

HeartRateScreen2::~HeartRateScreen2()
{
    delete ui;
}

bool HeartRateScreen2::event(QEvent *event)
{
    if(event->type() == POINTER_EVENT_TYPE){
        PointerEvent* pointerEvent = (PointerEvent*)event;

        if(pointerEvent->pointer == &speedSlider1 || pointerEvent->pointer == &speedSlider2){
            updateHistory();
        }
    }

    return AbstractMultiSliderScreen::event(event);
}

void HeartRateScreen2::setConstantGrade(){

    ui->backgroundLabel->setPixmap(QPixmap(QString(":/images/images/Heart-Rate-Control---(Fixed).png")));

    speedSlider2.hide();

    ageSlider.move(SLIDER_X, SLIDER3_Y);
    weightSlider.move(SLIDER_X, SLIDER4_Y);

    updateHistory();
}

void HeartRateScreen2::setDynamicGrade(){
    ui->backgroundLabel->setPixmap(QPixmap(QString(":/images/images/Heart-Rate-Control---(Dynamic).png")));

    speedSlider2.show();

    ageSlider.move(SLIDER_X, SLIDER4_Y);
    weightSlider.move(SLIDER_X, SLIDER5_Y);

    updateHistory();
}

void HeartRateScreen2::updateHistory()
{
    if(speedSlider2.isVisible()){
        AbstractMultiSliderScreen::updateHistory(speedSlider1.value, speedSlider2.value);
    }
    else{
        AbstractMultiSliderScreen::updateHistory(speedSlider1.value, speedSlider1.value);
    }
}

void HeartRateScreen2::on_invisibleButton_3_pressed()
{
    setConstantGrade();
}

void HeartRateScreen2::on_invisibleButton_4_pressed()
{
    setDynamicGrade();
}

void HeartRateScreen2::on_invisibleButton_6_pressed()
{
    Screens::show( new MainScreen(0, NULL) );

    close();
}

void HeartRateScreen2::on_invisibleButton_5_pressed()
{
    close();
}

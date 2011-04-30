#include "heartratescreen.h"
#include "ui_heartratescreen.h"

#include "mainscreen.h"
#include "pointerevent.h"
#include "screens.h"
#include "step.h"
#include "utils.h"

HeartRateScreen::HeartRateScreen(QWidget *parent) :
    AbstractMultiSliderScreen(parent)
    ,ui(new Ui::HeartRateScreen)
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

HeartRateScreen::~HeartRateScreen()
{
    delete ui;
}

bool HeartRateScreen::event(QEvent *event)
{
    if(event->type() == POINTER_EVENT_TYPE){
        PointerEvent* pointerEvent = (PointerEvent*)event;

        if(pointerEvent->pointer == &speedSlider1 || pointerEvent->pointer == &speedSlider2){
            updateHistory();
        }
    }

    return AbstractMultiSliderScreen::event(event);
}

void HeartRateScreen::setConstantGrade(){

    ui->backgroundLabel->setPixmap(QPixmap(QString(":/images/images/Heart-Rate-Control---(Fixed).png")));

    speedSlider2.hide();

    ageSlider.move(SLIDER_X, SLIDER3_Y);
    weightSlider.move(SLIDER_X, SLIDER4_Y);

    updateHistory();
}

void HeartRateScreen::setDynamicGrade(){
    ui->backgroundLabel->setPixmap(QPixmap(QString(":/images/images/Heart-Rate-Control---(Dynamic).png")));

    speedSlider2.show();

    ageSlider.move(SLIDER_X, SLIDER4_Y);
    weightSlider.move(SLIDER_X, SLIDER5_Y);

    updateHistory();
}

void HeartRateScreen::updateHistory()
{
    if(speedSlider2.isVisible()){
        AbstractMultiSliderScreen::updateHistory(speedSlider1.value, speedSlider2.value);
    }
    else{
        AbstractMultiSliderScreen::updateHistory(speedSlider1.value, speedSlider1.value);
    }
}

void HeartRateScreen::on_invisibleButton_3_pressed()
{
    setConstantGrade();
}

void HeartRateScreen::on_invisibleButton_4_pressed()
{
    setDynamicGrade();
}

void HeartRateScreen::on_invisibleButton_6_pressed()
{
    int minutes = (int) timeSlider.value;
    int lowSpeed = (int) speedSlider1.value;
    int age = (int) ageSlider.value;
    int weight = (int) weightSlider.value;

    int highSpeed;
    if(speedSlider2.isVisible()){
        highSpeed = (int) speedSlider2.value;
    }
    else{
        highSpeed = lowSpeed;
    }

    QList<Step*>* workout = Utils::createDynamicSpeedWorkout(minutes, lowSpeed, highSpeed, age, weight);
    Screens::show(new MainScreen(0, workout));

    close();
}

void HeartRateScreen::on_invisibleButton_5_pressed()
{
    close();
}
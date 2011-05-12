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
    ,lowPercentageSlider(this, 1, 100)
    ,highPercentageSlider(this, 1, 100)
{
    ui->setupUi(this);

    timeSlider.move(SLIDER_X,SLIDER1_Y);
    lowPercentageSlider.move(SLIDER_X,SLIDER2_Y);
    highPercentageSlider.move(SLIDER_X, SLIDER3_Y);

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

        if(pointerEvent->pointer == &lowPercentageSlider || pointerEvent->pointer == &highPercentageSlider){
            updateHistory();
        }
    }

    return AbstractMultiSliderScreen::event(event);
}

void HeartRateScreen::setConstantGrade(){

    ui->backgroundLabel->setPixmap(QPixmap(QString(":/images/images/Heart-Rate-Control---(Fixed).png")));

    highPercentageSlider.hide();

    ageSlider.move(SLIDER_X, SLIDER3_Y);
    weightSlider.move(SLIDER_X, SLIDER4_Y);

    updateHistory();
}

void HeartRateScreen::setDynamicGrade(){
    ui->backgroundLabel->setPixmap(QPixmap(QString(":/images/images/Heart-Rate-Control---(Dynamic).png")));

    highPercentageSlider.show();

    ageSlider.move(SLIDER_X, SLIDER4_Y);
    weightSlider.move(SLIDER_X, SLIDER5_Y);

    updateHistory();
}

void HeartRateScreen::updateHistory()
{
    int lowHistory = lowPercentageSlider.value/100 * historyWidget.historyHeight;

    int highHistory;
    if(highPercentageSlider.isVisible()){
         highHistory = highPercentageSlider.value/100 * historyWidget.historyHeight;
    }
    else{
        highHistory = lowHistory;
    }

     AbstractMultiSliderScreen::updateHistory(lowHistory, highHistory);
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
    float lowPercentage = lowPercentageSlider.value/100;
    int age = (int) ageSlider.value;
    int weight = (int) weightSlider.value;

    float highPercentage;
    if(highPercentageSlider.isVisible()){
        highPercentage = highPercentageSlider.value/100;
    }
    else{
        highPercentage = lowPercentage;
    }

    Workout* workout = Workout::createDynamicSpeedWorkout("Heart Rate", minutes, lowPercentage, highPercentage, age, weight);
    Screens::show(new MainScreen(0, workout));

    close();
}

void HeartRateScreen::on_invisibleButton_5_pressed()
{
    close();
}

#include "intervalscreen.h"
#include "ui_intervalscreen.h"

#include <QDebug>

#include "pointerevent.h"
#include "mainscreen.h"
#include "screens.h"
#include "utils.h"

IntervalScreen::IntervalScreen(QWidget *parent) :
    AbstractMultiSliderScreen(parent),
    ui(new Ui::IntervalScreen)
    ,timeSlider(this)
    ,lowGradeSlider(this)
    ,highGradeSlider(this)
    ,lowSpeedSlider(this)
    ,highSpeedSlider(this)
    ,ageSlider(this)
    ,weightSlider(this)
{
    ui->setupUi(this);

    timeSlider.move(SLIDER_X, SLIDER1_Y);
    lowGradeSlider.move(SLIDER_X, SLIDER2_Y);
    highGradeSlider.move(SLIDER_X, SLIDER3_Y);
    lowSpeedSlider.move(SLIDER_X, SLIDER2_Y);
    highSpeedSlider.move(SLIDER_X, SLIDER3_Y);
    ageSlider.move(SLIDER_X, SLIDER4_Y);
    weightSlider.move(SLIDER_X, SLIDER5_Y);

    on_invisibleButton_hills_pressed();

    ui->backgroundLabel->lower();
}

IntervalScreen::~IntervalScreen()
{
    delete ui;
}

void IntervalScreen::on_invisibleButton_hills_pressed()
{
    ui->backgroundLabel->setPixmap(QPixmap(QString(":/images/images/Interval---(Hills).png")));

    lowGradeSlider.show();
    highGradeSlider.show();

    lowSpeedSlider.hide();
    highSpeedSlider.hide();

    updateHistoryFromGrades();
}

void IntervalScreen::on_invisibleButton_4_pressed()
{
    ui->backgroundLabel->setPixmap(QPixmap(QString(":/images/images/Interval---(Sprints).png")));

    lowGradeSlider.hide();
    highGradeSlider.hide();

    lowSpeedSlider.show();
    highSpeedSlider.show();

    updateHistoryFromSpeeds();
}

bool IntervalScreen::event(QEvent *event)
{
    if(event->type() == POINTER_EVENT_TYPE){
        PointerEvent* pointerEvent = (PointerEvent*)event;

        if(pointerEvent->pointer == &lowGradeSlider || pointerEvent->pointer == &highGradeSlider){
            updateHistoryFromGrades();
        }
        else if(pointerEvent->pointer == &lowSpeedSlider || pointerEvent->pointer == &highSpeedSlider){
            updateHistoryFromSpeeds();
        }
    }

    return AbstractMultiSliderScreen::event(event);
}

void IntervalScreen::updateHistoryFromSpeeds()
{
    updateHistory(lowSpeedSlider.value, highSpeedSlider.value);
}

void IntervalScreen::updateHistoryFromGrades()
{
    updateHistory(lowGradeSlider.value, highGradeSlider.value);
}

void IntervalScreen::on_invisibleButton_hills_2_pressed()
{
    close();
}

void IntervalScreen::on_invisibleButton_hills_3_pressed()
{
    int minutes = timeSlider.value;
    int age = ageSlider.value;
    int weight = weightSlider.value;

    QList<Step*>* workout;
    if(lowSpeedSlider.isVisible()){

        int lowSpeed = lowSpeedSlider.value;
        int highSpeed = highSpeedSlider.value;

        workout = Utils::createDynamicSpeedWorkout(minutes, lowSpeed, highSpeed, age, weight);
    }
    else{

        int lowGrade = lowGradeSlider.value;
        int highGrade = highGradeSlider.value;

        workout = Utils::createDynamicGradeWorkout(minutes, lowGrade, highGrade, age, weight);
    }


    Screens::show(new MainScreen(0, workout));
    close();
}

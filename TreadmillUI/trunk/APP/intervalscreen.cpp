#include "intervalscreen.h"
#include "ui_intervalscreen.h"

#include <QDebug>

#include "pointerevent.h"
#include "mainscreen.h"
#include "screens.h"
#include "utils.h"
#include "preferences.h"

IntervalScreen::IntervalScreen(QWidget *parent) :
    AbstractMultiSliderScreen(parent),
    ui(new Ui::IntervalScreen)
    ,timeSlider(this)
    ,lowGradeSlider(this)
    ,highGradeSlider(this)
    ,lowSpeedSlider(this)
    ,highSpeedSlider(this)
    ,initialSpeedSlider(this)
    ,initialGradeSlider(this)
    ,weightSlider(this)
{
    ui->setupUi(this);

    timeSlider.move(SLIDER_X, SLIDER1_Y);
    lowGradeSlider.move(SLIDER_X, SLIDER2_Y);
    highGradeSlider.move(SLIDER_X, SLIDER3_Y);
    lowSpeedSlider.move(SLIDER_X, SLIDER2_Y);
    highSpeedSlider.move(SLIDER_X, SLIDER3_Y);
    initialGradeSlider.move(SLIDER_X, SLIDER4_Y);
    initialSpeedSlider.move(SLIDER_X, SLIDER4_Y);
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
    initialSpeedSlider.show();

    lowSpeedSlider.hide();
    highSpeedSlider.hide();
    initialGradeSlider.hide();

    updateHistoryFromGrades();
}

void IntervalScreen::on_invisibleButton_4_pressed()
{
    ui->backgroundLabel->setPixmap(QPixmap(QString(":/images/images/Interval---(Sprints).png")));

    lowGradeSlider.hide();
    highGradeSlider.hide();
    initialSpeedSlider.hide();

    lowSpeedSlider.show();
    highSpeedSlider.show();
    initialGradeSlider.show();

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
    int weight = weightSlider.value;

    Workout* workout;

    qDebug()<< "weight selected was: " << weight;
    if(lowSpeedSlider.isVisible()){

        int lowSpeed = lowSpeedSlider.value*10;
        int highSpeed = highSpeedSlider.value*10;

        workout = Workout::createDynamicSpeedWorkout("Speed Interval", minutes, lowSpeed, highSpeed, initialGradeSlider.value, weight);
    }
    else{

        int lowGrade = lowGradeSlider.value;
        int highGrade = highGradeSlider.value;

        workout = Workout::createDynamicGradeWorkout("Grade Interval", minutes, lowGrade, highGrade, initialSpeedSlider.value, weight);
    }

    MainScreen::getMainScreen()->startWorkout( workout);

    close();
}

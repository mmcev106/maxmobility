#include "fatburnscreen.h"
#include "ui_fatburnscreen.h"

#include "mainscreen.h"
#include "pointerevent.h"

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "screens.h"
#include "utils.h"
#include "preferences.h"

FatBurnScreen::FatBurnScreen(QWidget *parent) :
    AbstractMultiSliderScreen(parent),
    ui(new Ui::FatBurnScreen)
    ,timeSlider(this)
    ,intensitySlider(this)
    ,speedSlider(this)
    ,weightSlider(this)
{
    ui->setupUi(this);

    /*QMutex dummy;
    dummy.lock();
    QWaitCondition waitCondition;
    waitCondition.wait(&dummy, 500);*/

    historyWidget.move(HISTORY_X+1,HISTORY_Y+36);

    int x = 14;
    timeSlider.move(x,201);
    intensitySlider.move(x,320);
    speedSlider.move(x, 439);
    weightSlider.move(x,556);

    ui->backgroundLabel->lower();

    updateHistory();
}

FatBurnScreen::~FatBurnScreen()
{
    delete ui;
}

void FatBurnScreen::on_invisibleButton_7_pressed()
{
    close();
}

void FatBurnScreen::on_invisibleButton_6_pressed()
{
    int minutes = timeSlider.value;
    int weight = weightSlider.value;

    Workout* workout = Workout::createIntensityWorkout("Fat Burn", minutes, speedSlider.value, intensitySlider.getPercentage(), weight);
    MainScreen::getMainScreen()->startWorkout( workout);

    close();
}

void FatBurnScreen::updateHistory(){

    int midpoint = HISTORY_WIDTH/2;
    int value = speedSlider.value;

    for(int i=0;i<midpoint;i++){
        historyWidget.history[i] = value;
        value+=intensitySlider.value;
    }

    value-=intensitySlider.value;

    for(int i=midpoint;i<HISTORY_WIDTH;i++){
        historyWidget.history[i] = value;
        value-=intensitySlider.value;
    }

    historyWidget.repaint();
}

bool FatBurnScreen::event(QEvent *event)
{
    if(event->type() == POINTER_EVENT_TYPE){
        PointerEvent* pointerEvent = (PointerEvent*)event;

        if(pointerEvent->pointer == &intensitySlider || pointerEvent->pointer == &speedSlider){
            updateHistory();
        }
    }

    return AbstractMultiSliderScreen::event(event);
}

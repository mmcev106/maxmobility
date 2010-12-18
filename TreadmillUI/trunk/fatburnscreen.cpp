#include "fatburnscreen.h"
#include "ui_fatburnscreen.h"

#include "mainscreen.h"
#include "pointerevent.h"

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

FatBurnScreen::FatBurnScreen(QWidget *parent) :
    AbstractMultiSliderScreen(parent),
    ui(new Ui::FatBurnScreen)
    ,timeSlider(this)
    ,intensitySlider(this, 1, 25)
    ,weightSlider(this)
{
    ui->setupUi(this);

    /*QMutex dummy;
    dummy.lock();
    QWaitCondition waitCondition;
    waitCondition.wait(&dummy, 500);*/

    historyWidget.move(HISTORY_X+1,HISTORY_Y+36);

    int x = 14;
    timeSlider.move(x,275);
    intensitySlider.move(x,395);
    weightSlider.move(x,514);

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
    MainScreen* w = new MainScreen(0);
    w->show();

    close();
}

void FatBurnScreen::updateHistory(){

    int midpoint = HISTORY_WIDTH/2;
    int intensity = intensitySlider.value;

    for(int i=0;i<midpoint;i++){
        historyWidget.history[i] = intensity;
        intensity++;
    }

    intensity--;

    for(int i=midpoint;i<HISTORY_WIDTH;i++){
        historyWidget.history[i] = intensity;
        intensity--;
    }

    historyWidget.repaint();
}

bool FatBurnScreen::event(QEvent *event)
{
    if(event->type() == POINTER_EVENT_TYPE){
        PointerEvent* pointerEvent = (PointerEvent*)event;

        if(pointerEvent->pointer == &intensitySlider){
            updateHistory();
        }
    }

    return AbstractMultiSliderScreen::event(event);
}

#ifndef ABSTRACTMULTISLIDERSCREEN_H
#define ABSTRACTMULTISLIDERSCREEN_H

#include <QWidget>

#include "abstractscreen.h"
#include "historywidget.h"

class AbstractMultiSliderScreen : public AbstractScreen
{

public:
    AbstractMultiSliderScreen(QWidget *parent = 0);
    ~AbstractMultiSliderScreen();

protected:
    static const int SLIDER_X = 13;
    static const int SLIDER1_Y = 200;
    static const int SLIDER2_Y = 317;
    static const int SLIDER3_Y = 434;
    static const int SLIDER4_Y = 552;
    static const int SLIDER5_Y = 669;

    static const int HISTORY_WIDTH = 12;
    static const int HISTORY_HEIGHT = 30;

    static const int HISTORY_X= 746;
    static const int HISTORY_Y= 195;

    int* history;
    HistoryWidget historyWidget;

    void updateHistory(int low, int high);
};

#endif // ABSTRACTMULTISLIDERSCREEN_H

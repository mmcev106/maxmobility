#include "abstractmultisliderscreen.h"

AbstractMultiSliderScreen::AbstractMultiSliderScreen(QWidget* parent) : AbstractScreen(parent)
        ,history(new int[HISTORY_WIDTH])
        ,historyWidget(this, history, HISTORY_WIDTH, HISTORY_HEIGHT, BIG_BRICK_URL, HIGHLIGHTED_BIG_BRICK_URL)
{
    historyWidget.move(HISTORY_X,HISTORY_Y);
}

AbstractMultiSliderScreen::~AbstractMultiSliderScreen(){
    delete history;
}

void AbstractMultiSliderScreen::updateHistory(int low, int high){
    int* history = historyWidget.history;

    int value = low;
    for(int i=0; i<HISTORY_WIDTH; i+=2){
        history[i] = value;
        history[i+1] = value;

        if(value == low){
            value = high;
        }
        else{
            value = low;
        }
    }

    historyWidget.repaint();
}


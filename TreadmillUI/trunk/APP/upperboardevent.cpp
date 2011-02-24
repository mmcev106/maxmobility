#include "upperboardevent.h"

UpperBoardEvent::UpperBoardEvent( char heartRate,  char cadence) :
    QEvent(UPPER_BOARD_EVENT_TYPE)
{
        this->heartRate = heartRate;
        this->cadence = cadence;
}

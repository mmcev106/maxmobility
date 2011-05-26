#include "upperboardevent.h"

UpperBoardEvent::UpperBoardEvent( unsigned char heartRate,  unsigned char cadence) :
    QEvent(UPPER_BOARD_EVENT_TYPE)
{
        this->heartRate = heartRate;
        this->cadence = cadence;
}

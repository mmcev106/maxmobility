#include "upperboardevent.h"
// Wes added speed and grade from cadence
UpperBoardEvent::UpperBoardEvent( unsigned char *_msg) :

    QEvent(UPPER_BOARD_EVENT_TYPE)
{
    for (int i=0;i<8;i++)
        this->MessageData[i] = _msg[i];
}

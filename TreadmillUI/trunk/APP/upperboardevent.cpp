#include "upperboardevent.h"
// Wes added speed and grade from cadence
UpperBoardEvent::UpperBoardEvent( unsigned char heartRate,  unsigned char speed, unsigned char grade) :

    QEvent(UPPER_BOARD_EVENT_TYPE)
{
        this->heartRate = heartRate;
        this->speed = speed;
        this->grade = grade;
}

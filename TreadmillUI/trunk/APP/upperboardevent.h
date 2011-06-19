#ifndef UPPERBOARDEVENT_H
#define UPPERBOARDEVENT_H

#include <QEvent>

const QEvent::Type UPPER_BOARD_EVENT_TYPE = (QEvent::Type)2001;

class UpperBoardEvent : public QEvent
{
public:
    // Wes added speed and grade from cadence
    explicit UpperBoardEvent(unsigned char *_msg);
    char heartRate;
    char speed;
    char grade;
    unsigned char MessageData[8];

signals:

public slots:

};

#endif // UPPERBOARDEVENT_H

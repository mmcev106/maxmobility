#ifndef UPPERBOARDEVENT_H
#define UPPERBOARDEVENT_H

#include <QEvent>

const QEvent::Type UPPER_BOARD_EVENT_TYPE = (QEvent::Type)2001;

class UpperBoardEvent : public QEvent
{
public:
    // Wes added speed and grade from cadence
    explicit UpperBoardEvent(unsigned char heartRate, unsigned char speed, unsigned char grade);
    char heartRate;
    char speed;
    char grade;

signals:

public slots:

};

#endif // UPPERBOARDEVENT_H

#ifndef UPPERBOARDEVENT_H
#define UPPERBOARDEVENT_H

#include <QEvent>

const QEvent::Type UPPER_BOARD_EVENT_TYPE = (QEvent::Type)2001;

class UpperBoardEvent : public QEvent
{
public:
    explicit UpperBoardEvent( char heartRate,  char cadence);
    char heartRate;
    char cadence;

signals:

public slots:

};

#endif // UPPERBOARDEVENT_H

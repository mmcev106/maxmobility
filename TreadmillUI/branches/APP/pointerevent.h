#ifndef POINTEREVENT_H
#define POINTEREVENT_H

#include <QEvent>

const QEvent::Type POINTER_EVENT_TYPE = (QEvent::Type)2000;

class PointerEvent : public QEvent
{
public:
    PointerEvent(void* pointer);
    void* pointer;
};

#endif // POINTEREVENT_H

#include "pointerevent.h"

PointerEvent::PointerEvent(void * pointer) :
        QEvent(POINTER_EVENT_TYPE)
        ,pointer(pointer)
{
}

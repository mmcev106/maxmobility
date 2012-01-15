#include "videoplayer.h"

#include "pointerevent.h"
#include <QApplication>
#include <QDebug>

VideoPlayer::VideoPlayer(QWidget* parent) :
    Phonon::VideoPlayer(Phonon::VideoCategory, parent)
{
}

void VideoPlayer::mousePressEvent( QMouseEvent *evt ){
    PointerEvent* event = new PointerEvent(this);
    QApplication::postEvent(parent(), event);
}

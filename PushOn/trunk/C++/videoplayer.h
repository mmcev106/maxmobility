#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <phonon/VideoPlayer>

class VideoPlayer : public Phonon::VideoPlayer
{
public:
    VideoPlayer(QWidget* parent);

protected:
    void mousePressEvent( QMouseEvent *evt );
};

#endif // VIDEOPLAYER_H

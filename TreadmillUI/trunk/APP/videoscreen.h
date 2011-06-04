#ifndef VIDEOSCREEN_H
#define VIDEOSCREEN_H

#include <QWidget>

namespace Ui {
    class VideoScreen;
}

class VideoScreen : public QWidget
{
    Q_OBJECT

public:
    explicit VideoScreen(QWidget *parent = 0);
    ~VideoScreen();

private:
    Ui::VideoScreen *ui;
};

#endif // VIDEOSCREEN_H

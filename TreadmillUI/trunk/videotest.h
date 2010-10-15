#ifndef VIDEOTEST_H
#define VIDEOTEST_H

#include <QWidget>
#include <Phonon/VideoPlayer>

namespace Ui {
    class VideoTest;
}

class VideoTest : public QWidget
{
    Q_OBJECT

public:
    explicit VideoTest(QWidget *parent = 0);
    ~VideoTest();

private:
    Ui::VideoTest *ui;
    Phonon::VideoPlayer *player;
    QTimer *timer;
    double videoSpeed;
    void ensureManualPlayback();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void nextFrame();
    void play();
};

#endif // VIDEOTEST_H

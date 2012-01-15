#ifndef STARTUPWINDOW_H
#define STARTUPWINDOW_H

#include <QWidget>
#include "abstractscreen.h"
#include "videoplayer.h"
#include "messagescreen.h"
#include <QTimer>


namespace Ui {
    class StartupWindow;
}

class StartupWindow : public AbstractScreen
{
    Q_OBJECT

public:
    explicit StartupWindow(QWidget *parent = 0);
    ~StartupWindow();

public slots:
    void onSerialEvent(unsigned char* _data);
    void mockSerialEvent();

protected:
//    bool eventFilter(QObject * watched, QEvent *event);
    bool event(QEvent *event);

private:
    MessageScreen errorMessageScreen;
    Ui::StartupWindow *ui;
    VideoPlayer *player;
    Phonon::MediaSource* mediaSource;

    void showMainScreen(QString name, float speed, float grade, int minutes);
    QTimer sharedTimer;
    unsigned char* mockData;

private slots:
    void on_invisibleButton_16_pressed();
    void on_outdoorPathsButton_pressed();
    void on_invisibleButton_13_pressed();
    void on_invisibleButton_12_pressed();
    void on_invisibleButton_11_pressed();
    //void on_invisibleButton_14_pressed();
    void on_invisibleButton_9_pressed();
    void on_invisibleButton_10_pressed();
    void on_invisibleButton_8_pressed();
    void on_invisibleButton_6_pressed();
    void on_invisibleButton_5_pressed();
    void on_invisibleButton_4_pressed();
    void on_invisibleButton_3_pressed();
    void on_invisibleButton_2_pressed();
    void on_invisibleButton_pressed();
    void on_acc_invisibleButton_pressed();
    void sharedTimerTimeout();
    void restartVideo();
    void restartMusic();

};

#endif // STARTUPWINDOW_H
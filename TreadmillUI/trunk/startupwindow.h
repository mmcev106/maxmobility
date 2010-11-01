#ifndef STARTUPWINDOW_H
#define STARTUPWINDOW_H

#include <QWidget>
#include <phonon/VideoPlayer>

namespace Ui {
    class StartupWindow;
}

class StartupWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StartupWindow(QWidget *parent = 0);
    ~StartupWindow();

private:
    Ui::StartupWindow *ui;
    Phonon::VideoPlayer *player;

private slots:
    void on_invisibleButton_13_pressed();
    void on_invisibleButton_12_pressed();
    void on_invisibleButton_11_pressed();
    void on_invisibleButton_14_pressed();
    void on_invisibleButton_9_pressed();
    void on_invisibleButton_10_pressed();
    void on_invisibleButton_8_pressed();
    void on_invisibleButton_7_pressed();
    void on_invisibleButton_6_pressed();
    void on_invisibleButton_5_pressed();
    void on_invisibleButton_4_pressed();
    void on_invisibleButton_3_pressed();
    void on_invisibleButton_2_pressed();
    void on_invisibleButton_pressed();
    void restartVideo();
};

#endif // STARTUPWINDOW_H

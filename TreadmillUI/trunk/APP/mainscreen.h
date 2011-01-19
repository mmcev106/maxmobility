#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QTimer>
//#include <phonon/VideoPlayer>
#include "historywidget.h"
#include "audiosettingswidget.h"
#include <QKeyEvent>

namespace Ui {
    class MainScreen;
}

class MainScreen : public QWidget
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget *parent = 0, QString action = "");
    ~MainScreen();

protected:
//    void keyPressEvent ( QKeyEvent * event );

private:
    Ui::MainScreen *ui;
    void playVideo();
    int elapsedTime;
    QTimer *secondTimer;
    QTimer *playTimer;
//    Phonon::VideoPlayer *player;
    static const int HISTORY_LENGTH = 30;
//    int speedHistory[HISTORY_LENGTH];
//    int gradeHistory[HISTORY_LENGTH];
//    HistoryWidget speedHistoryWidget;
//    HistoryWidget gradeHistoryWidget;

    AudioSettingsWidget audioSettingsWidget;

private slots:
    void on_audioButton_invisibleButton_pressed();
    void on_videoThumbButton_invisibleButton_pressed();
    void updateDisplay();
};

#endif // MAINSCREEN_H
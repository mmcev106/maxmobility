#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QTimer>
#include <phonon/VideoPlayer>
#include "historywidget.h"

const int HISTORY_LENGTH = 30;

namespace Ui {
    class MainScreen;
}

class MainScreen : public QWidget
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget *parent = 0, QString action = "");
    ~MainScreen();

private:
    Ui::MainScreen *ui;
    int elapsedTime;
    QTimer *secondTimer;
    Phonon::VideoPlayer *player;
    int speedHistory[HISTORY_LENGTH];
    int gradeHistory[HISTORY_LENGTH];
    HistoryWidget speedHistoryWidget;
    HistoryWidget gradeHistoryWidget;

private slots:
    void updateDisplay();
};

#endif // MAINSCREEN_H

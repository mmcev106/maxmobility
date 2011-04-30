#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "abstractscreen.h"
#include <QTimer>
#include <phonon/VideoPlayer>
#include "historywidget.h"
#include "audiosettingswidget.h"
#include <QKeyEvent>
#include <QCloseEvent>
#include "step.h"
#include "workout.h"

namespace Ui {
    class MainScreen;
}

class MainScreen : public AbstractScreen
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget *parent, Workout* workout);
    ~MainScreen();

protected:
    bool eventFilter(QObject * watched, QEvent *event);
    void closeEvent(QCloseEvent * event);
//    void keyPressEvent(QKeyEvent* event);

private:
    Ui::MainScreen *ui;
    void playVideo();
    long startTime;
    QTimer *secondTimer;
    QTimer *milliSecondTimer;
    QTimer *playTimer;
    QLabel* trackWidget;
    QLabel* runningDudeWidget;
    int nextWorkoutStepIndex;
    long nextWorkoutStepTime;
    Workout* workout;
    double distance;
    Phonon::VideoPlayer *player;
    static const int HISTORY_LENGTH = 30;
//    int speedHistory[HISTORY_LENGTH];
//    int gradeHistory[HISTORY_LENGTH];
//    HistoryWidget speedHistoryWidget;
//    HistoryWidget gradeHistoryWidget;

    AudioSettingsWidget audioSettingsWidget;

    void writeHistoryEntry();

private slots:
    void on_audioButton_invisibleButton_pressed();
    void updateDisplay();
    void updateRunningDudeImage();
    void processNextWorkoutStep();

};

#endif // MAINSCREEN_H

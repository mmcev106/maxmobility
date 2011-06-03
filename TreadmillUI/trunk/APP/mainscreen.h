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
#include <QtOpenGL/QGLWidget>

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
    long startTime;
    QTimer *secondTimer;
    QTimer *milliSecondTimer;
    QTimer *playTimer;
    int nextWorkoutStepIndex;
    long nextWorkoutStepTime;
    Workout* workout;
    double distance;
    QSize centerSize;
    QWidget centerWidget;
    QLabel* trackWidget;
    QLabel* runningDudeWidget;
    static const int HISTORY_LENGTH = 5;
    int speedHistory[HISTORY_LENGTH];
    int gradeHistory[HISTORY_LENGTH];
    Phonon::VideoPlayer *player;
    HistoryWidget speedHistoryWidget;
    HistoryWidget gradeHistoryWidget;
//    static int Utils::getMAX_SPEED();
//    QGLWidget* glWidget;

    AudioSettingsWidget audioSettingsWidget;
    QPixmap videoMask;
    int speed;

    void writeHistoryEntry();
    void playVideo(QString filename);

private slots:
    void on_track_invisibleButton_pressed();
    void on_trails_invisibleButton_pressed();
    void on_tranquil_invisibleButton_pressed();
    void on_audioButton_invisibleButton_pressed();
    void updateDisplay();
    void updateRunningDudeImage();
    void processNextWorkoutStep();
    void restartVideo();
    void updateHistoryWidgets(int speed, int grade);
    void bumpHistoryWidgets();

};

#endif // MAINSCREEN_H

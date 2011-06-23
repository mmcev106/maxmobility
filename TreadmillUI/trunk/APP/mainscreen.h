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
#include <QWebView>
#include "WebWidget.h"
#include "tranquilselectionwidget.h"
#include "trailselectionwidget.h"
#include "scorewidget.h"

#define TRACK_VISUALIZATION 0
#define WEB_VISUALIZATION   1
#define VIDEO_VISUALIZATION 3
#define SCORE_VISUALIZATION 4

namespace Ui {
    class MainScreen;
}

class MainScreen : public AbstractScreen
{
    Q_OBJECT

public:
    static void createMainScreen(QWidget* parent);
    static MainScreen* getMainScreen();
    void startWorkout(Workout* workout);
    void recordWorkout(Workout* workout);
    void endWorkout();
    void hideWidgets(void);
    void recordSpeedChange(float speed);
    void recordGradeChange(float grade);

    ~MainScreen();

    void playVideo(QString filename);
    void ShowWidget(int selection,QString video, QString text);
//
protected:
    void closeEvent(QCloseEvent * event);
    void keyPressEvent(QKeyEvent* event);

private:
    WebWidget* webview;

    Ui::MainScreen *ui;
    long startTime;
    QTimer *secondTimer;
    QTimer *milliSecondTimer;
    QTimer *playTimer;
    QTimer *endTimer;
    int nextWorkoutStepIndex;
    long nextWorkoutStepTime;
    Workout* workout;
    float distance;
    QSize centerSize;
    QWidget centerWidget;
    QLabel* trackWidget;
    QLabel* runningDudeWidget;
    static const int HISTORY_LENGTH = 7;
    int speedHistory[HISTORY_LENGTH];
    int gradeHistory[HISTORY_LENGTH];
    Phonon::VideoPlayer *player;
    HistoryWidget speedHistoryWidget;
    HistoryWidget gradeHistoryWidget;
    AudioSettingsWidget audioSettingsWidget;
    ScoreWidget scoreWidget;
    void updateScoreWidgetText(long time, float speed, float grade);
    TranquilSelectionWidget tranquilSelectionWidget;
    TrailSelectionWidget trailSelectionWidget;
    void calculateCalories(int speed, int grade, long timeDifference);
    int stage;

    QPixmap videoMask;
    float speed,grade;
    int heartRate;
    int weight;
    int minutes, seconds;
    float calories;
    bool recordingWorkout;
    long lastStepRecordedTime;

    static MainScreen* mainScreen;

    explicit MainScreen(QWidget *parent);
    void writeHistoryEntry();

    void startWorkout(Workout* workout, bool recordWorkout);
    void recordWaitStep();

private slots:
    void on_track_invisibleButton_pressed();
    void on_web_invisibleButton_pressed();
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

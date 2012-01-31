#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QString>
#include <QColor>
#include <QApplication>
#include <QDir>

#include "qextserialport.h"
#include "state.h"
#include "mainscreen.h"
#include "workout.h"
#include "startupwindow.h"

static const bool MALE = true;
static const bool FEMALE = false;

static const bool STANDARD = true;
static const bool METRIC = false;

static const int MESSAGE_LENGTH = 8;

static const QColor HIGHLIGHT_BLUE(66, 180, 255, 200);
const static int AVERAGE_HEART_RATE_LENGTH=10;

class Preferences
{
private:
    static QString getCurrentDataPath();

public:
    static const QString FILENAME;

    static bool gender;
    static bool measurementSystem;
    static float speed,grade,heartRate;
    static float averageHeartRate;
    static int spd_diff,grd_diff;
    static int on_time,belt_time;
    static int age;
    static void setAge(int a);
    static int getAge();
    static float WALKING_SPEED;
    static float FAST_SPEED;
    static float JOGGING_SPEED;
    static float RUNNING_SPEED;

    static QApplication* application;

    const static int DEFAULT_FEEDBACK_SOUND_LEVEL;
    const static int DEFAULT_BACKGROUND_SOUND_LEVEL;

    static int feedbackSoundLevel;
    static int backgroundSoundLevel;

    static bool accessibilityMode;

    static State currentState;

    static State sendState;

    static bool hasSentState;

    static qint64 lastSerialMessageReceivedTime;
    static StartupWindow* startupWindow;

    static void setMeasurementSystem(bool Standard);    /*!< Used to set the Units system (mph/kph). */
    static bool getMeasurementSystem(void);             /*!< Used to read the state of the Units system. */

    static float getCurrentSpeed();                 /*!< Used to check the current speed value. */
    static void setCurrentSpeed(float spd);         /*!< Used to send a new speed value to lower board. */
    static float getCurrentGrade();                 /*!< Used to check the current grade value. */
    static void setCurrentGrade(float grd);         /*!< Used to send a new grade value to lower board. */

    static unsigned char getCurrentState();                /*!< Used to check the current state value. */
    static void setCurrentState(unsigned char _state);     /*!< Used to send a new state to the lower board. */

    static float getHeartRate();                 /*!< Used to check the current grade value. */
    static void setHeartRate(float hrtrt);         /*!< Used to send a new grade value to lower board. */

    static float getAverageHeartRate();                           /*!< Used to store last read in Heart Rate. */
    static float calculateAverageHeartRate(float thisHeartRate);    /*!< Used to calculate calories burned. */

    static void updateCurrentSpeed(float spd);      /*!< Used by serial listener thread to update the current speed. */
    static void updateCurrentGrade(float grd);      /*!< Used by serial listener thread to update the current grade. */
    static void updateCurrentState(unsigned char _state);  /*!< Used by serial listener thread to update the current state. */

    static QString getCurrentWorkoutsPath();
    static QString getCurrentHistoryPath();
    static bool isUsbDrivePresent();
    static bool isTestingMode();
};

#endif // PREFERENCES_H

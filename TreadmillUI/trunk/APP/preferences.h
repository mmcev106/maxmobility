#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QString>
#include <QColor>
#include <QApplication>
#include <QDir>

#include "qextserialport.h"
#include "state.h"

static const bool MALE = true;
static const bool FEMALE = false;

static const bool STANDARD = true;
static const bool METRIC = false;

static const int MESSAGE_LENGTH = 8;

static const QColor HIGHLIGHT_BLUE(66, 180, 255, 200);
const static int AVERAGE_HEART_RATE_LENGTH=50;

class Preferences
{
private:
    static void (*_spd_func)();
    static void (*_grd_func)();

    static QString getCurrentDataPath();
public:
    static const QString FILENAME;

    static bool gender;
    static bool measurementSystem;
    static int speed,grade,heartRate;
    static int averageHeartRate;
    static int spd_diff,grd_diff;
    static int on_time,belt_time;

    static char command;

    static int WALKING_SPEED;
    static int FAST_SPEED;
    static int JOGGING_SPEED;
    static int RUNNING_SPEED;

    static QThread* listener,*sender;

    static QextSerialPort* serialPort;
    static QApplication* application;

    static State currentState;

    static State sendState;

    static void setMeasurementSystem(bool Standard);    /*!< Used to set the Units system (mph/kph). */
    static bool getMeasurementSystem(void);             /*!< Used to read the state of the Units system. */

    static void setSpeedChangeFunction( void (*func)() );       /*!< Used to set the function that runs on a speed change. */
    static void setGradeChangeFunction( void (*func)() );       /*!< Used to set the function that runs on a grade change. */

    static int getCurrentSpeed();                 /*!< Used to check the current speed value. */
    static void setCurrentSpeed(int spd);         /*!< Used to send a new speed value to lower board. */
    static int getCurrentGrade();                 /*!< Used to check the current grade value. */
    static void setCurrentGrade(int grd);         /*!< Used to send a new grade value to lower board. */

    static unsigned char getCurrentState();                /*!< Used to check the current state value. */
    static void setCurrentState(unsigned char _state);     /*!< Used to send a new state to the lower board. */

    static int getHeartRate();                 /*!< Used to check the current grade value. */
    static void setHeartRate(int hrtrt);         /*!< Used to send a new grade value to lower board. */

    static int getAverageHeartRate();                           /*!< Used to store last read in Heart Rate. */
    static int calculateAverageHeartRate(int thisHeartRate);    /*!< Used to calculate calories burned. */


    static void updateCurrentSpeed(int spd);      /*!< Used by serial listener thread to update the current speed. */
    static void updateCurrentGrade(int grd);      /*!< Used by serial listener thread to update the current grade. */
    static void updateCurrentState(unsigned char _state);  /*!< Used by serial listener thread to update the current state. */

    static QString getCurrentWorkoutsPath();
    static QString getCurrentHistoryPath();
    static bool isUsbDrivePresent();
};

#endif // PREFERENCES_H

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

static const int BEAGLE_BOARD_MESSAGE_LENGTH = 7;

static const QColor HIGHLIGHT_BLUE(66, 180, 255, 200);

static const QString WORKOUTS = "workouts";
static const QString HISTORY = "history";

class Preferences
{
private:
    static int speed,grade;
    static int spd_diff,grd_diff;
    static void (*_spd_func)();
    static void (*_grd_func)();
public:
    static const QString FILENAME;

    static bool gender;
    static bool measurementSystem;

    static int WALKING_SPEED;
    static int FAST_SPEED;
    static int JOGGING_SPEED;
    static int RUNNING_SPEED;

    static QThread* listener,*sender;

    static QextSerialPort* serialPort;
    static QApplication* application;
    static QDir dataDirectory;

    static State currentState;

    static void setMeasurementSystem(bool Standard);    /*!< Used to set the Units system (mph/kph). */
    static bool getMeasurementSystem(void);             /*!< Used to read the state of the Units system. */

    static void setSpeedChangeFunction( void (*func)() );       /*!< Used to set the function that runs on a speed change. */
    static void setGradeChangeFunction( void (*func)() );       /*!< Used to set the function that runs on a grade change. */

    static int getCurrentSpeed();                 /*!< Used to check the current speed value. */
    static void setCurrentSpeed(int spd);         /*!< Used to send a new speed value to lower board. */
    static int getCurrentGrade();                 /*!< Used to check the current grade value. */
    static void setCurrentGrade(int grd);         /*!< Used to send a new grade value to lower board. */

    static void updateCurrentSpeed(int spd);      /*!< Used by serial listener thread to update the current speed. */
    static void updateCurrentGrade(int grd);      /*!< Used by serial listener thread to update the current grade. */

};

#endif // PREFERENCES_H

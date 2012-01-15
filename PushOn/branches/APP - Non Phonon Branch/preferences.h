#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QString>
#include <QColor>
#include <QApplication>

#include "qextserialport.h"
#include "state.h"

static const bool MALE = true;
static const bool FEMALE = false;

static const bool STANDARD = true;
static const bool METRIC = false;

static const int BEAGLE_BOARD_MESSAGE_LENGTH = 7;

static const QColor HIGHLIGHT_BLUE(66, 180, 255, 200);

static const QString WORKOUTS = "workouts";

class Preferences
{

public:
    static const QString FILENAME;

    static bool gender;
    static bool measurementSystem;


    static QextSerialPort* serialPort;
    static QApplication* application;

    static unsigned char messageData[BEAGLE_BOARD_MESSAGE_LENGTH];
    static State currentState;

    static float getCurrentSpeed();
    static void setCurrentSpeed(float speed);
    static float getCurrentGrade();
    static void setCurrentGrade(float grade);

};

#endif // PREFERENCES_H

#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QString>
#include <QColor>

//#include "qextserialport.h"

static const bool MALE = true;
static const bool FEMALE = false;

static const bool STANDARD = true;
static const bool METRIC = false;

static const QColor HIGHLIGHT_BLUE(66, 180, 255, 200);

static const QString WORKOUTS = "workouts";

class Preferences
{
private:
//    static QextSerialPort* _serialPort;

public:
    static const QString FILENAME;

    static bool gender;
    static bool measurementSystem;


//    static QextSerialPort* serialPort();
//    static void initializeSerialPort();
};

#endif // PREFERENCES_H

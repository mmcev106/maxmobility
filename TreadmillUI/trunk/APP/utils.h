#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include "step.h"
#include "workout.h"

static const float MAX_SPEED_MPH = 12.0;
static const float MAX_SPEED_KPH = 20.0;

static const float DEF_SPEED_MPH = 1.5;
static const float DEF_SPEED_KPH = 2.5;

static const float MAX_GRADE = 120;

static const bool STANDARD_UNITS = true;
static const bool METRIC_UNITS = false;

static const long MILLIS_PER_SECOND = 1000;
static const long MILLIS_PER_MINUTE = MILLIS_PER_SECOND * 60;
static const long MILLIS_PER_HOUR = MILLIS_PER_MINUTE * 60;

class Utils
{
public:
    static float getMAX_SPEED();
    Utils();
    static void setMAX_SPEED(bool Standard); // This will be called from the Preferences Class when unit system changes

    static float getDEF_SPEED();
    static void setDEF_SPEED(bool Standard);

    static QString toString(unsigned char*, int len);
    static int CRC(unsigned char* msg, int len);
private:
    static float MAX_SPEED;
    static float DEF_SPEED;
};

#endif // UTILS_H

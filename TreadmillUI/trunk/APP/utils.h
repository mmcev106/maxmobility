#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include "step.h"
#include "workout.h"

static const int MAX_SPEED_MPH = 12;
static const int MAX_SPEED_KPH = 20;

static const int MAX_GRADE = 12;

static const long MILLIS_PER_SECOND = 1000;
static const long MILLIS_PER_MINUTE = MILLIS_PER_SECOND * 60;
static const long MILLIS_PER_HOUR = MILLIS_PER_MINUTE * 60;

class Utils
{
public:
    int getMAX_SPEED();
    Utils();
    void setMAX_SPEED(bool Standard); // This will be called from the Preferences Class when unit system changes
    static QString toString(unsigned char*, int len);
private:
    static int MAX_SPEED;
};

#endif // UTILS_H

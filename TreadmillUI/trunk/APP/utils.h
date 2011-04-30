#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include "step.h"
#include "workout.h"

static const int MAX_SPEED = 12;
static const int MAX_GRADE = 10;

static const long MILLIS_PER_SECOND = 1000;
static const long MILLIS_PER_MINUTE = MILLIS_PER_SECOND * 60;
static const long MILLIS_PER_HOUR = MILLIS_PER_MINUTE * 60;

class Utils
{
public:
    Utils();
    static QString toString(unsigned char*, int len);
};

#endif // UTILS_H

#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include "step.h"

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
    static QList<Step*>* createDynamicSpeedWorkout(int minutes, int lowSpeed , int highSpeed, int age, int weight);
    static QList<Step*>* createWorkout(float speed, float grade, int minutes);
    static QList<Step*>* createDynamicGradeWorkout(int minutes, int lowGrade , int highGrade, int age, int weight);
    static QList<Step*>* createIntensityWorkout(int minutes, double percent, int weight);
};

#endif // UTILS_H

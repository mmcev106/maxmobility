#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include "step.h"

class Utils
{
public:
    Utils();
    static QString toString(unsigned char*, int len);
    static QList<Step*>* createDynamicSpeedWorkout(int minutes, int lowSpeed , int highSpeed, int age, int weight);
    static QList<Step*>* createWorkout(float speed, float grade, int minutes);
    static QList<Step*>* createDynamicGradeWorkout(int minutes, int lowGrade , int highGrade, int age, int weight);
//    static QList<Step*>* createDynamicGradeWorkout(int minutes, float lowGrade , float highGrade, int age, int weight);
//    static QList<Step*>* createIntensityWorkout(int minutes, int intensity, int weight);
};

#endif // UTILS_H

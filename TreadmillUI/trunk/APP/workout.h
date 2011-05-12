#ifndef WORKOUT_H
#define WORKOUT_H

#include <QString>
#include <QList>
#include "step.h"

class Workout
{
public:
    Workout(QString name, QList<Step*>* steps);
    ~Workout();

    QList<Step*>* steps;
    QString name;

    static Workout* createWorkout(QString name, float speed, float grade, int minutes);
    static Workout* createDynamicGradeWorkout(QString name, int minutes, int lowGrade , int highGrade, int age, int weight);
    static Workout* createIntensityWorkout(QString name, int minutes, int initialSpeed, double intensityPercent, int weight);
    static Workout* createDynamicSpeedWorkout(QString name, int minutes, int lowSpeed , int lowSpeed, int age, int weight);
    static Workout* createHeartRateWorkout(QString name, int minutes, float lowPercentage , float highPercentage, int age, int weight);
};

#endif // WORKOUT_H

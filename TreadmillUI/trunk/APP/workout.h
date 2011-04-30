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

    static Workout* createDynamicSpeedWorkout(QString name, int minutes, int lowSpeed , int highSpeed, int age, int weight);
    static Workout* createWorkout(QString name, float speed, float grade, int minutes);
    static Workout* createDynamicGradeWorkout(QString name, int minutes, int lowGrade , int highGrade, int age, int weight);
    static Workout* createIntensityWorkout(QString name, int minutes, double percent, int weight);
};

#endif // WORKOUT_H

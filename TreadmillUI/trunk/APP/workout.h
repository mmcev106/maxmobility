#ifndef WORKOUT_H
#define WORKOUT_H

#include <QString>
#include <QList>
#include "step.h"

class Workout
{
public:
    Workout(QString name, int weight);
    Workout(QString name, int weight, QList<Step*>* steps);
    ~Workout();

    QList<Step*>* steps;
    QString name;
    int _weight;

    static Workout* createWorkout(QString name, float speed, float grade, int minutes);
    static Workout* createDynamicGradeWorkout(QString name, int minutes, int lowGrade , int highGrade, int age, int weight);
    static Workout* createIntensityWorkout(QString name, int minutes, int initialSpeed, double intensityPercent, int weight);
    static Workout* createDynamicSpeedWorkout(QString name, int minutes, int lowSpeed , int highSpeed, int initialSpeed, int weight);
    static Workout* createHeartRateWorkout(QString name, int minutes, float lowPercentage , float highPercentage, int age, int weight);

    void save();
    static Workout* load(QString workoutName);
};

#endif // WORKOUT_H

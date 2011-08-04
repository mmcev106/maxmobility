#ifndef WORKOUT_H
#define WORKOUT_H

#include <QString>
#include <QList>
#include "step.h"

static int MIN_SPEED = 1;

class Workout
{
public:
    Workout(QString name, int weight);
    Workout(QString name, int weight, QList<Step*>* steps);
    ~Workout();

    QList<Step*>* steps;
    QString name;
    int _weight;
    float distance;
    int max_HR,min_HR;

    int visualization;
    QString scoreTitle;
    QString scoreResults;
    QString videoPath;

    static Workout* createWorkout(QString name, float speed, float grade, int minutes);
    static Workout* createDynamicGradeWorkout(QString name, int minutes, int lowGrade , int highGrade, int age, int weight);
    static Workout* createIntensityWorkout(QString name, int minutes, int initialSpeed, double intensityPercent, int weight);
    static Workout* createDynamicSpeedWorkout(QString name, int minutes, int lowSpeed , int highSpeed, int initialSpeed, int weight);
    static Workout* createHeartRateWorkout(QString name, int minutes, float lowPercentage , float highPercentage, int age, int weight);
    static Workout* createFitnessWorkout( int age, int weight, bool gender);
    static Workout* createFireFighterWorkout(int age, int weight, bool gender);
    static Workout* createAirForceWorkout(float initialSpeed, int age, int weight, bool gender);
    static Workout* createMarinesWorkout(float initialSpeed, int age, int weight, bool gender);
    static Workout* createNavyWorkout(float initialSpeed, int age, int weight, bool gender);
    static Workout* createArmyWorkout(float initialSpeed, int age, int weight, bool gender);

    void save();
    static Workout* load(QString workoutName);
    static Workout* load(QString workoutsDir, QString workoutName);

    static void increaseWorkoutIntensity(Workout* workout, float intensityPercentage);
    static float getMaxSpeed(Workout* workout);
    static float getMaxGrade(Workout* workout);

};

#endif // WORKOUT_H

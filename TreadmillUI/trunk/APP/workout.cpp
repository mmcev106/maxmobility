#include "workout.h"

#include "changegradestep.h"
#include "changespeedstep.h"
#include "waitstep.h"
#include "utils.h"
#include <QDebug>

static int MIN_SPEED = 1;

Workout::Workout(QString name, int weight=0, QList<Step*>* steps = new QList<Step*>()) :
        name(name)
        ,_weight(weight)
        ,steps(steps)
{
}

Workout::~Workout()
{
    if(steps != NULL){
        for(int i=0;i<steps->length();i++){
            delete steps->at(i);
        }

        delete steps;
    }
}

Workout* Workout::createWorkout(QString name, float speed, float grade, int minutes){

    Workout* workout = new Workout(name,0);
    QList<Step*> *steps = workout->steps;

    steps->append(new ChangeSpeedStep(speed));
    steps->append(new ChangeGradeStep(grade));
    steps->append(new WaitStep(minutes * MILLIS_PER_MINUTE));

    return workout;
}

Workout* Workout::createHeartRateWorkout(QString name, int minutes, float lowPercentage , float highPercentage, int initialSpeed, int weight){
    float range = Utils::getMAX_SPEED() - MIN_SPEED;
    float lowSpeed = MIN_SPEED + lowPercentage*range;
    float highSpeed = MIN_SPEED + highPercentage*range;

    return createDynamicSpeedWorkout(name, minutes, lowSpeed, highSpeed, 0, weight);
}

Workout* Workout::createDynamicSpeedWorkout(QString name, int minutes, int lowSpeed , int highSpeed, int initialGrade, int weight){

    Workout* workout = new Workout(name, weight);//, NULL, weight
    QList<Step*> *steps = workout->steps;

    qDebug() << "weight passed in was: " << weight;

    long sprintLength = MILLIS_PER_SECOND * 5;
    long endTime = MILLIS_PER_MINUTE * minutes;

    int sprints = endTime / sprintLength;

    steps->append(new ChangeGradeStep(initialGrade));

    for(int i=0; i< sprints; i++){

        if( i % 2 == 0 ){
            steps->append(new ChangeSpeedStep(lowSpeed));
        }
        else{
            steps->append(new ChangeSpeedStep(highSpeed));
        }

        steps->append(new WaitStep(sprintLength));
    }

    return workout;
}

Workout* Workout::createIntensityWorkout(QString name, int minutes, int startingSpeed, double intensityPercent, int weight){

    //adjust the percent, so that it goes between minimumPercent and 1 instead of 0 and 1
    double minimumPercent = .25;
    intensityPercent = intensityPercent + minimumPercent - intensityPercent*minimumPercent;

    qDebug() << "intensityPercent: " << intensityPercent;

    Workout* workout = new Workout(name, weight);//, NULL, weight
    QList<Step*> *steps = workout->steps;

    long currentTime = 0;
    long totalTime = minutes * MILLIS_PER_MINUTE;
    long halfTime = totalTime/2;
    long waitTime = MILLIS_PER_SECOND;
    int levels = halfTime/waitTime;

    int startingGrade = 0;
    float maxGradeChange = (MAX_GRADE - startingGrade)*intensityPercent;
    float maxSpeedChange = (Utils::getMAX_SPEED() - startingSpeed)*intensityPercent;

    qDebug() << "maxGradeChange: " << maxGradeChange;

    float gradeIncrement = maxGradeChange/levels;
    float speedIncrement = maxSpeedChange/levels;

    float speed = startingSpeed;
    float grade = startingGrade;

    steps->append(new ChangeGradeStep(grade));
    steps->append(new ChangeSpeedStep(speed));

    while(currentTime < halfTime){
        steps->append(new WaitStep(waitTime));

        grade += gradeIncrement;
        speed += speedIncrement;

        steps->append(new ChangeGradeStep(grade));
        steps->append(new ChangeSpeedStep(speed));

        currentTime += waitTime;
    }

    while(currentTime < totalTime){
        steps->append(new WaitStep(waitTime));

        grade -= gradeIncrement;
        speed -= speedIncrement;

        steps->append(new ChangeGradeStep(grade));
        steps->append(new ChangeSpeedStep(speed));

        currentTime += waitTime;
    }

    return workout;
}

Workout* Workout::createDynamicGradeWorkout(QString name, int minutes, int lowGrade , int highGrade, int initialSpeed, int weight){

    Workout* workout = new Workout(name, weight);//, NULL, weight
    QList<Step*> *steps = workout->steps;

    long sprintLength = MILLIS_PER_SECOND * 5;
    long endTime = MILLIS_PER_MINUTE * minutes;

    int sprints = endTime / sprintLength;

    steps->append(new ChangeSpeedStep(initialSpeed));

    for(int i=0; i< sprints; i++){

        if( i % 2 == 0 ){
            steps->append(new ChangeGradeStep(lowGrade));
        }
        else{
            steps->append(new ChangeGradeStep(highGrade));
        }

        steps->append(new WaitStep(sprintLength));
    }

    return workout;
}

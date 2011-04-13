#include "utils.h"

#include <QList>

#include "changegradestep.h"
#include "changespeedstep.h"
#include "waitstep.h"
#include <QDebug>

Utils::Utils()
{
}

QList<Step*>* Utils::createWorkout(float speed, float grade, int minutes){

    QList<Step*> *steps = new QList<Step*>();

    steps->append(new ChangeSpeedStep(speed));
    steps->append(new ChangeGradeStep(grade));
    steps->append(new WaitStep(minutes * MILLIS_PER_MINUTE));

    return steps;
}

QList<Step*>* Utils::createDynamicSpeedWorkout(int minutes, int lowSpeed , int highSpeed, int age, int weight){

    QList<Step*> *steps = new QList<Step*>();

    long sprintLength = MILLIS_PER_SECOND * 5;
    long endTime = MILLIS_PER_MINUTE * minutes;

    int sprints = endTime / sprintLength;

    steps->append(new ChangeGradeStep(0));

    for(int i=0; i< sprints; i++){

        if( i % 2 == 0 ){
            steps->append(new ChangeSpeedStep(lowSpeed));
        }
        else{
            steps->append(new ChangeSpeedStep(highSpeed));
        }

        steps->append(new WaitStep(sprintLength));
    }

    return steps;
}

QList<Step*>* Utils::createIntensityWorkout(int minutes, double intensityPercent, int weight){

    //adjust the percent, so that it goes between .1 and 1 instead of 0 and 1
    int minimumPercent = .1;
    intensityPercent = intensityPercent + minimumPercent - intensityPercent*minimumPercent;

    QList<Step*> *steps = new QList<Step*>();

    long currentTime = 0;
    long totalTime = minutes * MILLIS_PER_MINUTE;
    long halfTime = totalTime/2;
    long waitTime = MILLIS_PER_SECOND;
    int levels = halfTime/waitTime;

    int startingSpeed = 3;
    int startingGrade = 0;
    float maxGradeChange = (MAX_GRADE - startingGrade)*intensityPercent;
    float maxSpeedChange = (MAX_SPEED - startingSpeed)*intensityPercent;

    float gradeIncrement = maxGradeChange/levels;
    float speedIncrement = maxSpeedChange/levels;

    qDebug() << "speedIncrement: " << speedIncrement;

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

    return steps;
}

QList<Step*>* Utils::createDynamicGradeWorkout(int minutes, int lowGrade , int highGrade, int age, int weight){

    QList<Step*> *steps = new QList<Step*>();

    long sprintLength = MILLIS_PER_SECOND * 5;
    long endTime = MILLIS_PER_MINUTE * minutes;

    int sprints = endTime / sprintLength;

    steps->append(new ChangeSpeedStep(0));

    for(int i=0; i< sprints; i++){

        if( i % 2 == 0 ){
            steps->append(new ChangeGradeStep(lowGrade));
        }
        else{
            steps->append(new ChangeGradeStep(highGrade));
        }

        steps->append(new WaitStep(sprintLength));
    }

    return steps;
}

QString Utils::toString(unsigned char *array, int len){
    QString string;

    string = string.append( "{");
    for(int i=0;i<len;i++){

        if(i>0){
            string = string.append( ", ");
        }

       string = string.append(QString("%1").arg( array[i]));
    }
   string = string.append("}");

   return string;
}


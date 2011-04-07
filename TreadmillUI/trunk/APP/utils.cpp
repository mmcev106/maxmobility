#include "utils.h"

#include <QList>

#include "changegradestep.h"
#include "changespeedstep.h"
#include "waitstep.h"

static const long MILLIS_PER_SECOND = 1000;
static const long MILLIS_PER_MINUTE = MILLIS_PER_SECOND * 60;

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


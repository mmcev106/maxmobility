#include "workout.h"

#include <QDebug>
#include <QFile>

#include "changegradestep.h"
#include "changespeedstep.h"
#include "waitstep.h"
#include "utils.h"
#include "preferences.h"

static int MIN_SPEED = 1;

Workout::Workout(QString name, int weight) :
        name(name)
        ,_weight(weight)
        ,steps(new QList<Step*>())
{
}

Workout::Workout(QString name, int weight, QList<Step*>* steps) :
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

void Workout::save(){

    QString filename(Preferences::getCurrentWorkoutsPath() + "/" + name);
    QFile* workoutFile = new QFile(filename);

    while(workoutFile->exists()){
        delete workoutFile;
        filename = filename.append(" (2)");
        workoutFile = new QFile(filename);
    }

    workoutFile->open(QFile::ReadWrite);
    QTextStream stream(workoutFile);

    for(int i=0; i<steps->size(); i++){
        Step* step = steps->at(i);

        if(step->getType() == SPEED_CHANGE_TYPE){
            ChangeSpeedStep* changeSpeedStep = (ChangeSpeedStep*) step;
            stream << "speed\t" << changeSpeedStep->speed << "\n";
        }
        else if(step->getType() == GRADE_CHANGE_TYPE){
            ChangeGradeStep* changeGradeStep = (ChangeGradeStep*) step;
            stream << "grade\t" << changeGradeStep->grade << "\n";
        }
        else if(step->getType() == WAIT_TYPE){
            WaitStep* waitStep = (WaitStep*) step;
            stream << "wait\t" << waitStep->time << "\n";
        }
    }

    stream.flush();
    workoutFile->close();
}

Workout* Workout::load(QString workoutName){
    QFile file(Preferences::getCurrentWorkoutsPath() + "/" + workoutName);
    file.open(QFile::ReadOnly);
    QTextStream stream( &file );

    Workout* workout = new Workout(workoutName, 0);
    QList<Step*>* steps = workout->steps;
    QString line;

    while(( line = stream.readLine() ) != NULL){

        QStringList args = line.split('\t');

        QString stepType = args.at(0);

        if(stepType.compare("wait") == 0){
            long waitTime = QLocale(QLocale::C).toLongLong(args.at(1));
            steps->append(new WaitStep(waitTime));
        }
        else if(stepType.compare("grade") == 0){
            float grade = QLocale(QLocale::C).toFloat(args.at(1));
            steps->append(new ChangeGradeStep(grade));
        }
        else if(stepType.compare("speed") == 0){
            float speed = QLocale(QLocale::C).toFloat(args.at(1));
            steps->append(new ChangeSpeedStep(speed));
        }
    }

    file.close();

    return workout;
}

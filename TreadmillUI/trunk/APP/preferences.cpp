#include "preferences.h"
//#include "mainscreen.h"
#include "utils.h"
#include <QtDebug>
#include <QString>
#include "qdebug.h"


static QString PUSHON = "PushOn";
const QString Preferences::FILENAME = "Preferences.txt";

bool Preferences::gender = MALE;
bool Preferences::measurementSystem = STANDARD;

int Preferences::WALKING_SPEED;
int Preferences::FAST_SPEED;
int Preferences::JOGGING_SPEED;
int Preferences::RUNNING_SPEED;

QextSerialPort* Preferences::serialPort = NULL;
QApplication* Preferences::application = NULL;

QThread* Preferences::sender,*Preferences::listener;

State Preferences::currentState;

int Preferences::speed,Preferences::grade;
int Preferences::spd_diff,Preferences::grd_diff;
void (*Preferences::_spd_func)(void);
void (*Preferences::_grd_func)(void);

void Preferences::setMeasurementSystem(bool Standard)
{
    if (Standard == STANDARD)
    {
        measurementSystem = STANDARD;
        Utils::setMAX_SPEED(STANDARD);
    }
    else
    {
        measurementSystem = METRIC;
        Utils::setMAX_SPEED(METRIC);
    }
}

bool Preferences::getMeasurementSystem(void)
{
    return measurementSystem;
}

int Preferences::getCurrentSpeed(){
    return  speed;
}

void Preferences::setCurrentSpeed(int spd)
{
    if(spd > Utils::getMAX_SPEED())
        spd_diff = Utils::getMAX_SPEED();
    else
        spd_diff = spd;
}

int Preferences::getCurrentGrade(){
    return  grade;
}

void Preferences::setCurrentGrade(int grd){
    if(grd > MAX_GRADE)
        grd_diff = MAX_GRADE;
    else
        grd_diff = grd;
}

void Preferences::updateCurrentSpeed(int spd)
{
    if (spd!=speed)
//        MainScreen::updateDisplay();
//        _spd_func();
    if(spd > Utils::getMAX_SPEED())
        speed = Utils::getMAX_SPEED();
    else
        speed = spd;
}

void Preferences::setSpeedChangeFunction(void (*func)())
{
    _spd_func = func;
}

void Preferences::setGradeChangeFunction(void (*func)())
{
    _grd_func = func;
}

void Preferences::updateCurrentGrade(int grd){

    if (grd!=grade)
//        MainScreen::updateDisplay();
//        _grd_func();
    if(grd > MAX_GRADE)
        grade = MAX_GRADE;
    else
        grade = grd;
}

QString Preferences::getCurrentDataPath(){
    //qDebug() << "get current data path was called";
    QFileInfoList drives = QDir::drives();

    /**
      * Loop backwards through all drives except the first one
      * (which is assumed to be the C:)
      */

    for(int i=drives.length()-1; i>=1; i--){
        QFileInfo drive = drives.at(i);
        if(drive.isWritable()  && drive.absolutePath()!="C:/"){ // It was still using the C drive, so I told it not to. :) -Wes

            QDir driveDir(drive.filePath());
            //qDebug() << drive.absolutePath();
            driveDir.mkdir(PUSHON);
            return drive.filePath() + PUSHON;
        }
        else
        {}
            //qDebug() << "tried drive, " << drive.absolutePath() <<  " and failed.";
    }

    return NULL;
}

bool Preferences::isUsbDrivePresent(){
    return getCurrentDataPath() != NULL;
}

QString Preferences::getCurrentWorkoutsPath(){

    QString workouts = "workouts";

    QDir dataDir(getCurrentDataPath());
    dataDir.mkdir(workouts);

    return getCurrentDataPath() + "/" + workouts;
}

QString Preferences::getCurrentHistoryPath(){
    return getCurrentDataPath() + "/history";
}


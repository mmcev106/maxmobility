#include "preferences.h"
#include "utils.h"
#include <QDebug>


const QString Preferences::FILENAME = "Preferences.txt";

bool Preferences::gender = MALE;
bool Preferences::measurementSystem = STANDARD;

QextSerialPort* Preferences::serialPort = NULL;
QApplication* Preferences::application = NULL;

QDir Preferences::dataDirectory = QDir::current();

State Preferences::currentState;

float Preferences::speed,Preferences::grade;
float Preferences::spd_diff,Preferences::grd_diff;
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

float Preferences::getCurrentSpeed(){
    return  speed;
}

void Preferences::setCurrentSpeed(float spd)
{
    if(spd > Utils::getMAX_SPEED())
        spd_diff = Utils::getMAX_SPEED();
    else
        spd_diff = spd;
}

float Preferences::getCurrentGrade(){
    return  grade;
}

void Preferences::setCurrentGrade(float grd){
    if(grd > MAX_GRADE)
        grd_diff = MAX_GRADE;
    else
        grd_diff = grd;
}

void Preferences::updateCurrentSpeed(float spd)
{
    if (spd!=speed)
        _spd_func();
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

void Preferences::updateCurrentGrade(float grd){

    if (grd!=grade)
        _grd_func();
    if(grd > MAX_GRADE)
        grade = MAX_GRADE;
    else
        grade = grd;
}

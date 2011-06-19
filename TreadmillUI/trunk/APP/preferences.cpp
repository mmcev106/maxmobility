#include "preferences.h"
//#include "mainscreen.h"
#include "utils.h"
#include <QDebug>
#include <QString>
#include <QHostInfo>

static QString PUSHON = "PushOn";
const QString Preferences::FILENAME = "Preferences.txt";

bool Preferences::gender = MALE;

bool Preferences::measurementSystem = STANDARD;

float Preferences::WALKING_SPEED;
float Preferences::FAST_SPEED;
float Preferences::JOGGING_SPEED;
float Preferences::RUNNING_SPEED;

QextSerialPort* Preferences::serialPort = NULL;
QApplication* Preferences::application = NULL;

QThread* Preferences::sender,*Preferences::listener;

State Preferences::currentState;
State Preferences::sendState;

float Preferences::speed=0,Preferences::grade=0,Preferences::heartRate=0,Preferences::averageHeartRate=0;
int Preferences::spd_diff,Preferences::grd_diff;
int Preferences::on_time,Preferences::belt_time;
char Preferences::command=0;
void (*Preferences::_spd_func)(void);
void (*Preferences::_grd_func)(void);

void Preferences::setMeasurementSystem(bool Standard)
{
    if (Standard == STANDARD)
    {
        measurementSystem = STANDARD;
        command = 1;
        Utils::setMAX_SPEED(STANDARD);
        Utils::setDEF_SPEED(STANDARD);
    }
    else
    {
        command = 0;
        measurementSystem = METRIC;
        Utils::setMAX_SPEED(METRIC);
        Utils::setDEF_SPEED(METRIC);
    }
}

bool Preferences::getMeasurementSystem(void)
{
    return measurementSystem;
}

int Preferences::getCurrentSpeed(){
    return  speed;
}

void Preferences::setCurrentSpeed(float spd)
{
    if(spd > Utils::getMAX_SPEED())
        spd_diff = Utils::getMAX_SPEED();
    else
        spd_diff = (int)(spd*10) | (1<<7);
}

unsigned char Preferences::getCurrentState()
{
    return currentState.state;
}

void Preferences::setCurrentState(unsigned char _state)
{
    bool units = getMeasurementSystem();
    char st = (units) ? (UNITS_MASK|_state):_state;
    st |= STATE_CHANGE_MASK;
    sendState.sendstate = st; //st;
//    qDebug() << "Change state "<<Utils::toString(&sendState.sendstate,1) ;
//    qDebug() << "current state "<<Utils::toString(&currentState.state,1) ;
}

void Preferences::updateCurrentState(unsigned char _state)
{
    currentState.state = _state;
}

int Preferences::getHeartRate(){

    int thisHeartRate=heartRate;
    if (thisHeartRate<50)
        thisHeartRate=0;

     return  thisHeartRate;
}

int Preferences::getAverageHeartRate(){
    return averageHeartRate;
}

int Preferences::calculateAverageHeartRate(int thisHeartRate){
    static int heartRates=0;
    static int i=0;
    static int sum=0;
    heartRates+=thisHeartRate;
    i++;

    if (i==AVERAGE_HEART_RATE_LENGTH)
    {
        averageHeartRate=heartRates/AVERAGE_HEART_RATE_LENGTH;
        heartRates=0;
        sum=0;
        i=0;
    }
}

void Preferences::setHeartRate(int hrtrt)
{
    heartRate=hrtrt;
    calculateAverageHeartRate(heartRate);
}

int Preferences::getCurrentGrade(){
    return  grade;
}

void Preferences::setCurrentGrade(float grd){
    if(grd > MAX_GRADE)
        grd_diff = MAX_GRADE;
    else
        grd_diff = (int)(grd*10) | (1<<7);
}

void Preferences::updateCurrentSpeed(float spd)
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

void Preferences::updateCurrentGrade(float grd){

    if (grd!=grade)
//        MainScreen::updateDisplay();
//        _grd_func();
    if(grd > MAX_GRADE)
        grade = MAX_GRADE;
    else
        grade = grd;
}

QString Preferences::getCurrentDataPath(){
    QFileInfoList drives = QDir::drives();

    /**
      * Loop backwards through all drives except the first one
      * (which is assumed to be the C:)
      */

    for(int i=drives.length()-1; i>=1; i--){
        QFileInfo drive = drives.at(i);
        if(drive.isWritable()  && drive.absolutePath()!="C:/" && drive.absolutePath()!="Z:/" ){ // It was still using the C drive, so I told it not to. :) -Wes

            QDir driveDir(drive.filePath());
            driveDir.mkdir(PUSHON);
            return drive.filePath() + PUSHON;
        }
    }

    //used for testing
    if( isTestingMode() ){
        return "/PushOn";
    }

    return NULL;
}

bool Preferences::isTestingMode(){
    if( QHostInfo::localHostName().compare("Mark-McEvers-MacBook.local") == 0){
        return true;
    }

    return false;
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


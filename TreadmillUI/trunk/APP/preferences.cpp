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

int Preferences::feedbackSoundLevel = 70;
int Preferences::backgroundSoundLevel = 30;

bool Preferences::accessibilityMode = false;

bool Preferences::hasSentState = true;

float Preferences::WALKING_SPEED;
float Preferences::FAST_SPEED;
float Preferences::JOGGING_SPEED;
float Preferences::RUNNING_SPEED;
int Preferences::age;

QextSerialPort* Preferences::serialPort = NULL;
QApplication* Preferences::application = NULL;

QThread* Preferences::sender,*Preferences::listener;

State Preferences::currentState;
State Preferences::sendState;

float Preferences::speed=0,Preferences::grade=0,Preferences::heartRate=0,Preferences::averageHeartRate=0;
int Preferences::spd_diff=0,Preferences::grd_diff=0;
int Preferences::on_time=0,Preferences::belt_time=0;

void Preferences::setMeasurementSystem(bool Standard)
{
    if (Standard == STANDARD)
    {
        measurementSystem = STANDARD;
        Utils::setMAX_SPEED(STANDARD);
        Utils::setDEF_SPEED(STANDARD);
        currentState.state |= UNITS_MASK;
        sendState.state |= UNITS_MASK;
    }
    else
    {
        measurementSystem = METRIC;
        Utils::setMAX_SPEED(METRIC);
        Utils::setDEF_SPEED(METRIC);
        currentState.state &= ~(UNITS_MASK);
        sendState.state &= ~(UNITS_MASK);
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
    if (spd>Utils::getMAX_SPEED())
        spd = Utils::getMAX_SPEED();
    if (spd<0.0f)
        spd = 0.0f;
    if (spd>speed)
        spd_diff = ((int)((spd-speed)*10)) | (1<<7);
    else
        spd_diff = (int)((speed-spd)*10);
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
    sendState.sendstate = st;
    hasSentState = false;
}

void Preferences::updateCurrentState(unsigned char _state)
{
    currentState.state = _state;
    if (hasSentState)
        sendState.sendstate = _state;
}

float Preferences::getHeartRate(){

    int thisHeartRate=heartRate;
    if (thisHeartRate<50)
        thisHeartRate=0;

     return  thisHeartRate;
}

float Preferences::getAverageHeartRate(){
    return averageHeartRate;
}

float Preferences::calculateAverageHeartRate(float thisHeartRate){
    static float heartRates=0;
    static int i=0;
    static float sum=0;
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

void Preferences::setHeartRate(float hrtrt)
{
    heartRate=hrtrt;
    calculateAverageHeartRate(heartRate);
}

float Preferences::getCurrentGrade(){
    return  grade;
}

void Preferences::setCurrentGrade(float grd){
    if (grd>12.0f)
        grd = 12.0f;
    if (grd<0.0f)
        grd = 0.0f;
    if (grd>grade)
        grd_diff = ((int)((grd-grade)*10)) | (1<<7);
    else
        grd_diff = (int)((grade-grd)*10);
}

void Preferences::updateCurrentSpeed(float spd)
{
    if(spd > Utils::getMAX_SPEED())
        speed = Utils::getMAX_SPEED();
    else
        speed = spd;
}

void Preferences::updateCurrentGrade(float grd)
{
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
    else if( QHostInfo::localHostName().compare("MarkMax-PC") == 0){
        return true;
    }
    else if( QHostInfo::localHostName().compare("virtualbox_xp") == 0){
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

int Preferences::getAge(){
    return age;
}
void Preferences::setAge(int a){
    age=a;
}


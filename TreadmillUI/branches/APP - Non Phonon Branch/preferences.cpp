#include "preferences.h"
#include <QDebug>

const QString Preferences::FILENAME = "Preferences.txt";

bool Preferences::gender = MALE;
bool Preferences::measurementSystem = STANDARD;

QextSerialPort* Preferences::serialPort = NULL;
QApplication* Preferences::application = NULL;

unsigned char Preferences::messageData[BEAGLE_BOARD_MESSAGE_LENGTH];

State Preferences::currentState;

float Preferences::getCurrentSpeed(){
    float speed = messageData[1];
    speed /= 10;

    return  speed;
}

void Preferences::setCurrentSpeed(float speed)
{
    messageData[1] = (unsigned char) (speed * 10) ;
}

float Preferences::getCurrentGrade(){
    float speed = messageData[2];
    speed /= 10;

    return  speed;
}

void Preferences::setCurrentGrade(float grade){
    messageData[2] = (unsigned char) (grade * 10);
}
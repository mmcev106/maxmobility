#include "preferences.h"

const QString Preferences::FILENAME = "Preferences.txt";

bool Preferences::gender = MALE;
bool Preferences::measurementSystem = STANDARD;

QextSerialPort* Preferences::serialPort = NULL;
QApplication* Preferences::application = NULL;

unsigned char Preferences::messageData[BEAGLE_BOARD_MESSAGE_LENGTH];

State Preferences::currentState;

unsigned char Preferences::getCurrentSpeed(){
    return messageData[1];
}

void Preferences::setCurrentSpeed(unsigned char speed){
    messageData[1] = speed;
}

unsigned char Preferences::getCurrentGrade(){
    return messageData[2];
}

void Preferences::setCurrentGrade(unsigned char grade){
    messageData[2] = grade;
}

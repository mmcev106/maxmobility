#include "preferences.h"

const QString Preferences::FILENAME = "Preferences.txt";

bool Preferences::gender = MALE;
bool Preferences::measurementSystem = STANDARD;

QextSerialPort* Preferences::serialPort = NULL;
QApplication* Preferences::application = NULL;

unsigned char Preferences::messageData[BEAGLE_BOARD_MESSAGE_LENGTH];

State Preferences::currentState;

#include "serialsenderthread.h"
#include <QDebug>
#include "preferences.h"
#include "utils.h"
#include "state.h"

static int MESSAGE_DELAY = 250;

SerialSenderThread::SerialSenderThread()
{
}

void SerialSenderThread::run(){

    QextSerialPort* port =  Preferences::serialPort;

    unsigned char* messageData = Preferences::messageData;
    messageData[0] = 0xFF;
    messageData[1] = 1;
    messageData[2] = 1;
    messageData[3] = 0;
    messageData[4] = 0;
    messageData[5] = 0;
    messageData[6] = '\n';

    Preferences::currentState.state = &messageData[3];

    while(true){

        qDebug() << "Sending: " << Utils::toString( messageData, BEAGLE_BOARD_MESSAGE_LENGTH );
        port->write((char*)messageData);
        port->flush();

        msleep(MESSAGE_DELAY);
    }
}

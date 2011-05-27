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

//    unsigned char* messageData = Preferences::messageData;

    while(true){

//        qDebug() << "Sending: " << Utils::toString( messageData, BEAGLE_BOARD_MESSAGE_LENGTH );
//        port->write((char*)messageData);
        port->flush();

        msleep(MESSAGE_DELAY);
    }
}

#include "seriallistenerthread.h"

#include "qdebug.h"
#include "preferences.h"
#include "qextserialport.h"
#include "upperboardevent.h"
#include "QApplication"
#include "utils.h";

static const int READ_WAIT_LIMIT = 1000 * 60 * 5;
static const int MESSAGE_LENGTH = 8;

SerialListenerThread::SerialListenerThread()
{
}

void SerialListenerThread::run(){
    QextSerialPort* port =  Preferences::serialPort;

//    int x = 0;
    while(port->waitForReadyRead( READ_WAIT_LIMIT)){
        QByteArray data = port->read(MESSAGE_LENGTH);
        /*unsigned char rawData[8];
        rawData[0] = 0xFF;
        rawData[2] = x;
        rawData[3] = x;
        rawData[7] = '\n';
        QByteArray data((char*)rawData, 8);*/

        if(data.length() < 100){
            qDebug() << "Received Data: " << Utils::toString ( (unsigned char* )data.data(), data.length());
        }


        if(data.length() != MESSAGE_LENGTH){
            qDebug() << "The message received was not the correct length!  It was " << data.length() << " bytes long.";
        }
        else{
            handleMessage((unsigned  char*)data.data());
        }

        QThread::sleep(2);
//        x++;
    }
}

void SerialListenerThread::handleMessage(unsigned char* data){

    if(data[0] != 0xFF){
        qDebug() << "Ignoring message because the first byte was not 0xFF";
        return;
    }

    unsigned char _state = data[1];
    char heartRate = data[2];
    char speed = data[3];
    unsigned char grade = data[4];  // Wes updated these to speed and grade from cadence and rawData
    char crcMsb = data[5];
    char crcLsb = data[6];

    if(data[7] != '\n'){
        qDebug() << "Ignoring message because the last byte was not a new line!";
        return;
    }

    State state;
    state.state = &_state;

    UpperBoardEvent event(heartRate, speed, grade); // wes updated this to speed and grade from cadence
    QApplication::sendEvent(Preferences::application,  &event);

    // Update History widgets

}

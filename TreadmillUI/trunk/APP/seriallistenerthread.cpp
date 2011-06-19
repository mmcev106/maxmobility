#include "seriallistenerthread.h"

#include "qdebug.h"
#include "preferences.h"
#include "qextserialport.h"
#include "upperboardevent.h"
#include "QApplication"
#include "utils.h"
#include "calibrationscreen.h"
#include "settingsscreen.h"
#include "startupwindow.h"

static const int READ_WAIT_LIMIT = 0;//1000 * 60 * 5

SerialListenerThread::SerialListenerThread()
{
}

void SerialListenerThread::run(){

    QextSerialPort* port =  Preferences::serialPort;

    while(port->isOpen()){     //port->waitForReadyRead( READ_WAIT_LIMIT )
        QByteArray data = port->read(MESSAGE_LENGTH);

        if(data.length() < 100 && data.length() > 0){
            qDebug() << "Received Data: " << Utils::toString ( (unsigned char* )data.data(), data.length());
        }


        if(data.length() != MESSAGE_LENGTH){
            qDebug() << "The message received was not the correct length!  It was " << data.length() << " bytes long.";
        }
        else{
            handleMessage((unsigned  char*)data.data());
        }

        QThread::msleep(100);
    }
}

void SerialListenerThread::handleMessage(unsigned char* data){

    if(data[0] != 0xFF){
        qDebug() << "Ignoring message because the first byte was not 0xFF";
        return;
    }

    int crcMsb = data[5];
    int crcLsb = data[6];

    if(data[7] != '\n'){
        qDebug() << "Ignoring message because the last byte was not a new line!";
        return;
    }
    int _crc = crcMsb*256 + crcLsb;
    if (_crc != Utils::CRC(data,5))
    {
        qDebug() << "Ignoring message because the CRC's didn't match!";
        qDebug() << "MSG CRC = " << _crc;
        qDebug() << "My CRC = " << Utils::CRC(data,5);
        return;
    }


    emit triggerSerialEvent(data);
//    UpperBoardEvent event(data);
//    QApplication::sendEvent(Preferences::application, &event);
}

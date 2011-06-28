#include "seriallistenerthread.h"

#include <QDebug>
#include <QApplication>

#include "preferences.h"
#include "qextserialport.h"
#include "upperboardevent.h"
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
        }

        if(data.length() != MESSAGE_LENGTH){
        }
        else{
            QByteArray _data = data;
            handleMessage((unsigned  char*)_data.data());
        }

        QThread::msleep(100);
    }
}

void SerialListenerThread::handleMessage(unsigned char* data){

    if(data[0] != 0xFF){
        return;
    }

    int crcMsb = data[5];
    int crcLsb = data[6];

    if(data[7] != '\n'){
        return;
    }
    int _crc = crcMsb*256 + crcLsb;
    if (_crc != Utils::CRC(data,5))
    {
        return;
    }


    qDebug() << "Received Data: " << Utils::toString ( data, 8);
    emit triggerSerialEvent(data);
}

#include "seriallistenerthread.h"

#include "qdebug.h"
#include "preferences.h"
#include "qextserialport.h"

static const int READ_WAIT_LIMIT = 1000 * 60 * 5;

SerialListenerThread::SerialListenerThread()
{
}

void SerialListenerThread::run(){
    qDebug() << "asdfasdf";
//    QextSerialPort* port =  Preferences::serialPort;

//    while(port->waitForReadyRead( READ_WAIT_LIMIT)){
//        char* data = port;
//    }
}

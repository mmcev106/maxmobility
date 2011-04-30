#include <iostream>

#include <QtGui/QApplication>
#include <qfile.h>
#include <QTextStream>
#include <QtDebug>
#include <QDir>

#include "qextserialport.h"
#include "qextserialenumerator.h"
#include "startupwindow.h"
#include "preferences.h"
#include "screens.h"
#include "seriallistenerthread.h"
#include "serialsenderthread.h"
#include "state.h"

using namespace std;

void loadPreferences(){
    QFile file(Preferences::FILENAME);
    if(file.exists()){
        file.open(QFile::ReadOnly);

        QDataStream stream(&file);

        stream >> Preferences::measurementSystem;

        file.close();
    }
}

void savePreferences(){
    QFile file(Preferences::FILENAME);
    file.open(QFile::WriteOnly);
    QDataStream stream(&file);

    stream << Preferences::measurementSystem;

    file.close();
}

void initializeSerialPortConnection(){

    unsigned char* messageData =  Preferences::messageData;
    messageData[0] = 0xFF;
    messageData[1] = 1;
    messageData[2] = 1;
    messageData[3] = 0;
    messageData[4] = 0;
    messageData[5] = 0;
    messageData[6] = '\n';

    Preferences::currentState.state = &messageData[3];

    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();

    if(ports.length() < 2){
        qDebug() << "A second serial port was not found.  Disabling serial communication.";
        return;
    }

    QString portName = ports.at(1).portName;

    if(!portName.startsWith("/dev/")){
        portName = portName.prepend("/dev/");
    }

    qDebug() << "Serial Port: " + portName;

    QextSerialPort* port = new QextSerialPort(portName, QextSerialPort::EventDriven);
    port->setBaudRate(BAUD56000);
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_2);
    bool open = port->open(QextSerialPort::ReadWrite);

    if(open){

        Preferences::serialPort = port;

        (new SerialListenerThread())->start();
        (new SerialSenderThread())->start();
    }else{
        qDebug() << "An error occurred while opening the serial port!";
    }
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Preferences::application=&a;

    QDir::setCurrent(QCoreApplication::applicationDirPath());

    loadPreferences();

    initializeSerialPortConnection();

    ( new StartupWindow())->showFullScreen();

    a.exec();

    savePreferences();

    return 0;
}
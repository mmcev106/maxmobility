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

    QString portName = QextSerialEnumerator::getPorts().at(0).portName;

    QextSerialPort* port = new QextSerialPort(portName, QextSerialPort::EventDriven);
    port->setBaudRate(BAUD56000);
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_2);

    Preferences::serialPort = port;

    (new SerialListenerThread())->start();
    (new SerialSenderThread())->start();
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

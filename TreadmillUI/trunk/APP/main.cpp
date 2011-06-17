#include <iostream>

#include <QtGui/QApplication>
#include <qfile.h>
#include <QTextStream>
#include <QtDebug>
#include <QDir>
#include <QCoreApplication>

#include "qextserialport.h"
#include "qextserialenumerator.h"
#include "startupwindow.h"
#include "preferences.h"
#include "screens.h"
#include "seriallistenerthread.h"
#include "serialsenderthread.h"
#include "state.h"
#include "utils.h"
#include "settingsscreen.h"
#include "calibrationscreen.h"

using namespace std;

void loadPreferences(){
    bool tempMeasurementSystem;
    QFile file(Preferences::FILENAME);
    if(file.exists()){
        file.open(QFile::ReadOnly);

        QDataStream stream(&file);
        //read the file
        stream >> tempMeasurementSystem;

        file.close();
        Preferences::setMeasurementSystem(tempMeasurementSystem);
    }

    int maxSpeed;
    if (Preferences::measurementSystem == STANDARD)
        maxSpeed=MAX_SPEED_MPH;
    else
        maxSpeed=MAX_SPEED_KPH;

    Preferences::WALKING_SPEED=maxSpeed/4;
    Preferences::FAST_SPEED=maxSpeed/2;
    Preferences::JOGGING_SPEED=maxSpeed*.75;
    Preferences::RUNNING_SPEED=maxSpeed;
}

void savePreferences(){
    QFile file(Preferences::FILENAME);
    file.open(QFile::WriteOnly);
    QDataStream stream(&file);

    stream << Preferences::measurementSystem;

    file.close();
}

void initializeSerialPortConnection(){

//    unsigned char* messageData =  Preferences::messageData;
//    messageData[0] = 0xFF;
//    messageData[1] = 1;
//    messageData[2] = 1;
//    messageData[3] = 0;
//    messageData[4] = 0;
//    messageData[5] = 0;
//    messageData[6] = '\n';

//    Preferences::currentState.state = &messageData[3];

    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();

    QString portName = ports.at(0).portName;
    QStringList list;
    qDebug() << "Serial Port: " + portName;
    list = portName.split(QRegExp("\\W+"));
    QString name = list.last();
    qDebug() << "Actual Port: " + name;

    QextSerialPort* port = new QextSerialPort(name, QextSerialPort::EventDriven);
    port->setBaudRate(BAUD9600);
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_1);
    qDebug() << "Opening Port.";
    bool open = port->open(QextSerialPort::ReadWrite);

//    bool open = false;

    if(open){
        Preferences::serialPort = port;
        qDebug() << "Port Opened!" + Preferences::serialPort->readLine();

        Preferences::listener = new SerialListenerThread();
        Preferences::listener->start();
        Preferences::sender = new SerialSenderThread();
        Preferences::sender->start();
    }else{
        qDebug() << "An error occurred while opening the serial port!";
    }
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("PushOn");
    Preferences::application=&a;

    QString workingDir = QCoreApplication::applicationDirPath();
    QDir::setCurrent(workingDir);
    qDebug() << "Working Directory: " << workingDir;

    loadPreferences();

    initializeSerialPortConnection();

    StartupWindow* startupWindow = new StartupWindow();
    MainScreen::createMainScreen(startupWindow);
    SettingsScreen::createSettingsScreen(startupWindow);
    CalibrationScreen::createCalibrationScreen(startupWindow);

    Screens::show(startupWindow);
    a.exec();

    savePreferences();

    return 0;
}

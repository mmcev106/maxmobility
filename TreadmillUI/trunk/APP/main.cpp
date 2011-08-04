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

    Preferences::setMeasurementSystem(STANDARD);
    if (Preferences::measurementSystem == STANDARD)
    {
        Preferences::WALKING_SPEED=2.0;
        Preferences::FAST_SPEED=3.0;
        Preferences::JOGGING_SPEED=6.0;
        Preferences::RUNNING_SPEED=8.0;
    }
    else
    {
        Preferences::WALKING_SPEED=3.0;
        Preferences::FAST_SPEED=6.0;
        Preferences::JOGGING_SPEED=10.0;
        Preferences::RUNNING_SPEED=14.0;
    }

}

void savePreferences(){
    QFile file(Preferences::FILENAME);
    file.open(QFile::WriteOnly);
    QDataStream stream(&file);

    stream << Preferences::measurementSystem;

    file.close();
}

void initializeSerialPortConnection(StartupWindow* _window){

    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();

//    QString portName = ports.back().portName;
    QString portName = ports.front().portName;

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

    if(open){
        Preferences::serialPort = port;
        qDebug() << "Port Opened!" + Preferences::serialPort->readLine();

        Preferences::listener = new SerialListenerThread();
        Preferences::listener->start();
        Preferences::sender = new SerialSenderThread();
        Preferences::sender->start();
        QObject::connect(Preferences::listener,SIGNAL(triggerSerialEvent(unsigned char*)),_window,SLOT(onSerialEvent(unsigned char*)));
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

    StartupWindow* startupWindow = new StartupWindow();
    MainScreen::createMainScreen(startupWindow);
    SettingsScreen::createSettingsScreen(startupWindow);
    CalibrationScreen::createCalibrationScreen(startupWindow);

    initializeSerialPortConnection(startupWindow);

    Utils::InitAudio(startupWindow);

    Screens::show(startupWindow);
    a.exec();


    savePreferences();

    return 0;
}

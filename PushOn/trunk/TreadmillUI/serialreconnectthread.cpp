#include "serialreconnectthread.h"

#include <QFile>
#include <QList>
#include <QDebug>

#include "preferences.h"


int ONE_SECOND = 1000;

SerialReconnectThread::SerialReconnectThread()
{
}

void SerialReconnectThread::run(){
    initializeSerialPortConnection();

    while(true){
        qint64 minimumMessageTime = QDateTime::currentMSecsSinceEpoch();
        msleep(ONE_SECOND * 3);

        if(Preferences::lastSerialMessageReceivedTime < minimumMessageTime){
            qDebug() << "A serial message was not received in the expected time frame, reconnecting.....";

            qDebug() << "Closing the old serial port connection.....";
            if(port->isOpen()){
                port->close();
            }

            //wait for the previous listener and sender threads to complete

            qDebug() << "Waiting for the listener thread to complete.....";
            if(listener && listener->isRunning()){
                listener->wait();
            }

            qDebug() << "Waiting for the sender thread to complete.....";
            if(sender && sender->isRunning()){
                sender->wait();
            }

            qDebug() << "Cleaning up old resources.....";
            delete listener, sender, port;
            listener = 0;
            sender = 0;

            qDebug() << "Initializing the new serial port connection.....";
            initializeSerialPortConnection();
        }
    }
}

void SerialReconnectThread::initializeSerialPortConnection(){

    QFile serialFile("serial.txt");

    QString portName;
    if(serialFile.exists()){
        serialFile.open(QFile::ReadOnly);
        QTextStream stream(&serialFile);

        portName = stream.readLine();
    }
    else{

        QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();

    //    portName = ports.back().portName;
        portName = ports.front().portName;
    }

    QStringList list;
    qDebug() << "Serial Port: " + portName;
    list = portName.split(QRegExp("\\W+"));
    QString name = list.last();

    if(Preferences::isTestingMode()){
        name = "/dev/null";
    }

    qDebug() << "Actual Port: " + name;

    port = new QextSerialPort(name, QextSerialPort::EventDriven);
    port->setBaudRate(BAUD9600);
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_1);
    qDebug() << "Opening Port.";

    listener = 0;
    sender = 0;

    if(port->open(QextSerialPort::ReadWrite)){
        qDebug() << "Port Opened!";

        listener = new SerialListenerThread(port);
        listener->start();
        sender = new SerialSenderThread(port);
        sender->start();
        QObject::connect(listener,SIGNAL(triggerSerialEvent(unsigned char*)),Preferences::startupWindow,SLOT(onSerialEvent(unsigned char*)));
    }else{
        qDebug() << "An error occurred while opening the serial port!";
    }
}

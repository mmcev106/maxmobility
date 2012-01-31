#ifndef SERIALRECONNECTTHREAD_H
#define SERIALRECONNECTTHREAD_H

#include <QThread>

#include "qextserialport.h"
#include "qextserialenumerator.h"

#include "seriallistenerthread.h"
#include "serialsenderthread.h"
#include "startupwindow.h"

class SerialReconnectThread : public QThread
{
    Q_OBJECT

public:
    SerialReconnectThread();
    void run();

private:
    void initializeSerialPortConnection();
    QextSerialPort* port;
    SerialListenerThread* listener;
    SerialSenderThread* sender;
};

#endif // SERIALRECONNECTTHREAD_H

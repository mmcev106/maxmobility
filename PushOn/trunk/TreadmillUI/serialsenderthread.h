#ifndef SERIALSENDERTHREAD_H
#define SERIALSENDERTHREAD_H

#include <QThread>

#include "qextserialport.h"

class SerialSenderThread : public QThread
{
public:
    SerialSenderThread(QextSerialPort* port);
    void run();

private:
    QextSerialPort* port;
};

#endif // SERIALSENDERTHREAD_H

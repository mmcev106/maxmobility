#ifndef SERIALLISTENERTHREAD_H
#define SERIALLISTENERTHREAD_H

#include <QThread>
#include <QByteArray>

#include "qextserialport.h"

class SerialListenerThread : public QThread
{
    Q_OBJECT

public:
    SerialListenerThread(QextSerialPort* port);
    void run();

signals:
    void triggerSerialEvent(unsigned char* _data);

private:
    void handleMessage(unsigned char* data);
    QextSerialPort* port;
};

#endif // SERIALLISTENERTHREAD_H

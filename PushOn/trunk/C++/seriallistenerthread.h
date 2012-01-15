#ifndef SERIALLISTENERTHREAD_H
#define SERIALLISTENERTHREAD_H

#include <QThread>
#include <QByteArray>

class SerialListenerThread : public QThread
{
    Q_OBJECT

public:
    SerialListenerThread();
    void run();

signals:
    void triggerSerialEvent(unsigned char* _data);

private:
    void handleMessage(unsigned char* data);
};

#endif // SERIALLISTENERTHREAD_H

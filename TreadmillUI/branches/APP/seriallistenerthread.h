#ifndef SERIALLISTENERTHREAD_H
#define SERIALLISTENERTHREAD_H

#include <QThread>
#include <QByteArray>

class SerialListenerThread : public QThread
{
public:
    SerialListenerThread();
    void run();

private:
    void handleMessage(unsigned char* data);
};

#endif // SERIALLISTENERTHREAD_H

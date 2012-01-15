#ifndef SERIALSENDERTHREAD_H
#define SERIALSENDERTHREAD_H

#include <QThread>

class SerialSenderThread : public QThread
{
public:
    SerialSenderThread();
    void run();
};

#endif // SERIALSENDERTHREAD_H

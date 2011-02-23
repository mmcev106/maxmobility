#ifndef SERIALLISTENERTHREAD_H
#define SERIALLISTENERTHREAD_H

#include <QThread>

class SerialListenerThread : public QThread
{
public:
    SerialListenerThread();
    void run();
};

#endif // SERIALLISTENERTHREAD_H

#ifndef WORKER_H
#define WORKER_H

#include "runnable.h"
#include <QString>
#include <QThread>

class Worker : public Runnable
{
private:
    QThread* thread;
public:
    Worker();
    ~Worker();
    void run() = 0;
    QString id() = 0;
};

#endif // WORKER_H

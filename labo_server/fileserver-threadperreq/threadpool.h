#ifndef THREADPOOL_H
#define THREADPOOL_H
#include "runnable.h"
#include <QThread>
#include <QVector>

class ThreadPool
{
private:
    int maxThreadCount;
    QVector<QThread> threadsVector;

public:
    ThreadPool(int maxThreadCount);
    void start(Runnable* runnable);
};

#endif // THREADPOOL_H

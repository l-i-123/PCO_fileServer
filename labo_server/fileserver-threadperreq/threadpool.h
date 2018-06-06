#include "runnabletask.h"
#include <QThread>
#include <QVector>
#include "request.h"
#include "hoaremonitor.h"
#include "worker.h"

#ifndef THREADPOOL_H
#define THREADPOOL_H

class ThreadPool : public HoareMonitor
{
    Q_OBJECT
private:

    QVector<bool> threadAvailable;
    int poolThreadCapacity;
    int poolThreadUsed;
    Condition waitCond;

    QVector<Worker*> threadsVector;
    QVector<RunnableTask*> runnableVector;
    bool hasDebugLog;

    int threadAvailible();

public:
    ThreadPool(int poolThreadCapacity, bool hasDebugLog);
    ThreadPool(int poolThreadCapacity);
    ~ThreadPool();
    void start(RunnableTask* runnable);
public slots:
    void runnableFinished();

};

#endif // THREADPOOL_H

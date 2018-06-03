#include "runnable.h"
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
    int maxThreadCount;
    QVector<QThread*> threadsVector;
    QVector<Runnable*> runnableVector;

    int threadCreateCount;
    int threadBusyCount;
    Condition allThreadBusy;
    QVector<bool> freeThread;

public:
    ThreadPool(int maxThreadCount);
    void start(Runnable* runnable);


public slots:
    void handleThreadEnd(int number);

signals:
    void newRunnable(Runnable* runnable);
};

#endif // THREADPOOL_H

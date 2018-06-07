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

public:
    ThreadPool(int poolThreadCapacity, bool hasDebugLog);
    ThreadPool(int poolThreadCapacity);
    ~ThreadPool();
    void start(Runnable* runnable);
    void put(Runnable* item);
    Runnable* get(void);
    int nbWaitingConso;
    int nbWaitingProd;

    class WorkerThread: public QThread
    {
        friend ThreadPool;

    public:
        WorkerThread(ThreadPool* poolPointer);
        void setNewRunnable(Runnable* newRunnable);
        Runnable* runnable;
    private:
        ThreadPool* poolPointer;

    protected:
        void run() Q_DECL_OVERRIDE;
    };

private:

    QVector<bool> threadAvailable;
    int poolThreadCapacity;
    int poolThreadUsed;
    Condition waitCond;

    QVector<WorkerThread*> threadsVector;
    QVector<Runnable*> runnableVector;
    bool hasDebugLog;

    int threadAvailible();
    Condition waitConso;
    Condition waitProd;
};

#endif // THREADPOOL_H

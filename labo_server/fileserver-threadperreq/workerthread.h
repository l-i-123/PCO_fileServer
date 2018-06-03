#include <QThread>
#include "threadpool.h"

#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H


class WorkerThread: public QThread
{
private:
    //ThreadPool* threadpool;

public:
    //WorkerThread(ThreadPool* threadpool);
    void run();
};

#endif // WORKERTHREAD_H

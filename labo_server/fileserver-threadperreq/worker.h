#include <QThread>
#include "runnabletask.h"

#ifndef WORKER_H
#define WORKER_H


class Worker: public QThread
{
    Q_OBJECT
public:
    Worker(RunnableTask* runnable);
    void setNewRunnable(RunnableTask* newRunnable);
    RunnableTask* runnable;

protected:
    void run() Q_DECL_OVERRIDE;

signals:
    void runnableEnd();

private:

};

#endif // WORKER_H

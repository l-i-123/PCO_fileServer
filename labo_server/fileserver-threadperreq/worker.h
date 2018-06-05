#include <QThread>
#include "runnable.h"

#ifndef WORKER_H
#define WORKER_H


class Worker: public QThread
{
    Q_OBJECT
public:
    Worker(Runnable* runnable);
    void setNewRunnable(Runnable* newRunnable);
    Runnable* runnable;

protected:
    void run() Q_DECL_OVERRIDE;

signals:
    void runnableEnd();

private:

};

#endif // WORKER_H

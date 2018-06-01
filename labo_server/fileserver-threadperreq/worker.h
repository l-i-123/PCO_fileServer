#include <QThread>
#include "runnable.h"

#ifndef WORKER_H
#define WORKER_H


class Worker: public QThread
{
    Q_OBJECT
public:
    Worker(Runnable* runnable);

protected:
    void run() Q_DECL_OVERRIDE;

private:
    Runnable* runnable;


signals:
    void runnableEnd(int threadNumer);
};

#endif // WORKER_H

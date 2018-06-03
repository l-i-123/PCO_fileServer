#include <QThread>
#include "runnable.h"

#ifndef WORKER_H
#define WORKER_H


class Worker: public QThread
{
    Q_OBJECT
public:
    Worker(Runnable* runnable, int id);

protected:
    void run() Q_DECL_OVERRIDE;

private:
    Runnable* runnable;
    bool waitRunnable;
    int threadId;

signals:
    void runnableEnd(int threadNumber);

public slots:
    void newRunnable(Runnable* runnable);
};

#endif // WORKER_H

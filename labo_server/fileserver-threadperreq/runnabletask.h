#ifndef RUNNABLETASK_H
#define RUNNABLETASK_H

#include "runnable.h"
#include "request.h"
#include <QString>
#include <QThread>
#include "abstractbuffer.h"
#include <QObject>

class RunnableTask : public Runnable
{
private:
    Request request;
    AbstractBuffer<Response>* responsesBuffer;
    int myId;
    bool hasDebugLog;
public:
    RunnableTask(Request request, AbstractBuffer<Response>* responsesBuffer, int myId, bool hasDebugLog);
    ~RunnableTask();
    void run();
    QString id();
};

#endif // RUNNABLETASK

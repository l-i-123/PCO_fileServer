#ifndef RUNNABLETASK_H
#define RUNNABLETASK_H
#include <QString>
#include "request.h"
#include "response.h"
#include "abstractbuffer.h"
#include "requesthandler.h"
#include "runnable.h"

class RunnableTask: public Runnable
{
private:
    Request request;
    AbstractBuffer<Response>* responsesBuffer;
    bool hasDebugLog;
    RequestHandler* reqHandler;
    QString myId;
public:
    RunnableTask(Request request, AbstractBuffer<Response>* responsesBuffer, QString myId, bool hasDebugLog);

    void run();

    QString id();
};

#endif // RUNNABLETASK_H

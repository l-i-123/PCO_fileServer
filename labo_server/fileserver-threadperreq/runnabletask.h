#ifndef RUNNABLETASK_H
#define RUNNABLETASK_H
#include <QString>
#include "request.h"
#include "response.h"
#include "abstractbuffer.h"
#include "runnable.h"
#include "requesthandler.h"

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
    RunnableTask(Request request, QString myId);

    //Le runnable sans paramètre à été ajouté afin de pouvoir lancer les tests fourni par le prof
    RunnableTask();
    void run();

    QString id();
};

#endif // RUNNABLETASK_H

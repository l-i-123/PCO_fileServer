#include <QThread>
#include "request.h"
#include "requesthandler.h"
#include "response.h"
#include "mesabuffer.h"

#ifndef SENDREQUESTTHREAD_H
#define SENDREQUESTTHREAD_H


class SendRequestThread: public QThread
{
private:

Request request;
AbstractBuffer<Response>* responsesBuffer;
RequestHandler* reqHandler;
bool hasDebugLog;
Response response;

public:
    SendRequestThread(Request request, AbstractBuffer<Response>* responsesBuffer, bool hasDebugLog);
    void run();
};

#endif // SENDREQUESTTHREAD_H

#ifndef REQUESTDISPATCHERTHREAD_H
#define REQUESTDISPATCHERTHREAD_H

#include "abstractbuffer.h"
#include "mesabuffer.h"
#include "request.h"
#include <QThread>
#include "sendrequestthread.h"
#include "response.h"

class RequestDispatcherThread : public QThread
{
public:
    RequestDispatcherThread(AbstractBuffer<Request>* requestsBuffer, AbstractBuffer<Response>* responsesBuffer);

protected:
    void run();

private:
    AbstractBuffer<Request>* requestsBuffer;
    AbstractBuffer<Response>* responsesBuffer;
    QVector<SendRequestThread> threadVector;
    Request request;
    Response response;
};

#endif // REQUESTDISPATCHERTHREAD_H

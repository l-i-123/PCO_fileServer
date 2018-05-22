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
    RequestDispatcherThread(MesaBuffer<Request>* requestsBuffer, MesaBuffer<Response>* responsesBuffer);

protected:
    void run();

private:
    MesaBuffer<Request>* requestsBuffer;
    MesaBuffer<Response>* responsesBuffer;
    QVector<SendRequestThread> threadVector;
    Request request;
    Response response;
};

#endif // REQUESTDISPATCHERTHREAD_H

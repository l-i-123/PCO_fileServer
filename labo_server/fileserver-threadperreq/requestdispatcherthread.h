/**
 * Description:     Prototype of the class which takes the requests in the buffer and use the class
 *                  SendRequestThread to send the request to the server.
 * Name of file:    requestdispatcherthread.h
 * Authors:         NDjoli Elie
 *                  Silva Miguel
 * Date:            16.05.2018
 */

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
    RequestDispatcherThread(AbstractBuffer<Request>* requestsBuffer, AbstractBuffer<Response>* responsesBuffer, bool hasDebugLog);

protected:
    void run();

private:
    /* Buffer of the requests */
    AbstractBuffer<Request>* requestsBuffer;
    /* Buffer of the responses */
    AbstractBuffer<Response>* responsesBuffer;
    Request request;
    Response response;
    bool hasDebugLog;
};

#endif // REQUESTDISPATCHERTHREAD_H

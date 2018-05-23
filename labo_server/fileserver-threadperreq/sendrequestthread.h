/**
 * Description:     Prototype of the class which sends the requests to the server and
 *                  then add the response in the buffer responses.
 * Name of file:    sendrequestthread.h
 * Authors:         NDjoli Elie
 *                  Silva Miguel
 * Date:            16.05.2018
 */

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
/* Buffer of the response */
AbstractBuffer<Response>* responsesBuffer;
/* Object to make the request in the server */
RequestHandler* reqHandler;
bool hasDebugLog;
Response response;

public:

    /**
     * Method sending a request to the server and then add the respnse of the server in the response buffer
     * @brief SendRequestThread
     * @param request
     * @param responsesBuffer
     * @param hasDebugLog
     */
    SendRequestThread(Request request, AbstractBuffer<Response>* responsesBuffer, bool hasDebugLog);

    void run();
};

#endif // SENDREQUESTTHREAD_H

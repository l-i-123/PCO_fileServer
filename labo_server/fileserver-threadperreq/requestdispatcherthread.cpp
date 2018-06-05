/**
 * Description:     Class which takes the requests in the buffer and use the class
 *                  SendRequestThread to send the request to the server.
 * Name of file:    requestdispatcherthread.cpp
 * Authors:         NDjoli Elie
 *                  Silva Miguel
 * Date:            16.05.2018
 */

#include "requestdispatcherthread.h"
#include "sendrequestthread.h"
#include "runnable.h"
#include "runnabletask.h"
#include <QVector>
#include <QThread>

RequestDispatcherThread::RequestDispatcherThread(AbstractBuffer<Request>* requestsBuffer, AbstractBuffer<Response>* responsesBuffer, bool hasDebugLog){
    this->requestsBuffer = requestsBuffer;
    this->responsesBuffer = responsesBuffer;
    this->hasDebugLog = hasDebugLog;
    this->threadPool = new ThreadPool(QThread::idealThreadCount(), hasDebugLog);
}

void RequestDispatcherThread::run(){

    while(true){

        request = requestsBuffer->get();
        Runnable *task = new Runnable(request, responsesBuffer, hasDebugLog);
        threadPool->start(task);

    }

}

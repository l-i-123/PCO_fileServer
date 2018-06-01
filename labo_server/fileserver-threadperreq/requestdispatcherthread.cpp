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
    this->threadPool = new ThreadPool(QThread::idealThreadCount());
}

void RequestDispatcherThread::run(){

    while(true){
        //SendRequestThread* newThread;

        /* Waiting on value in the request buffer */
        request = requestsBuffer->get();

        Runnable *task = new Runnable(request, responsesBuffer, 1, hasDebugLog);

        threadPool->start(task);

        /* Send a signal when the thread is finished. It means that it can be deleted
           This part between the signal and the slot is a little bit more complex
           Check the link: http://doc.qt.io/archives/qt-4.8/signalsandslots.html */
        //connect(newThread, &SendRequestThread::finished, newThread, &QObject::deleteLater);
        //newThread->start();
    }

}

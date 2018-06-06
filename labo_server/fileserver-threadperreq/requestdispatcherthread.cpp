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
#include <QVector>
#include <QThread>
#include <QString>

RequestDispatcherThread::RequestDispatcherThread(AbstractBuffer<Request>* requestsBuffer, AbstractBuffer<Response>* responsesBuffer, bool hasDebugLog){
    this->requestsBuffer = requestsBuffer;
    this->responsesBuffer = responsesBuffer;
    this->hasDebugLog = hasDebugLog;
    this->threadPool = new ThreadPool(QThread::idealThreadCount(), hasDebugLog);
}

void RequestDispatcherThread::run(){
    int runnableId = 0;
    while(true){
        //Récupération de la requête dans le buffer de buffer
        request = requestsBuffer->get();

        //Création d'une tâche
        Runnable *task = new Runnable(request, responsesBuffer, QString::number(runnableId++), hasDebugLog);

        //Lancemen de la tâche dans le thread pool
        threadPool->start(task);
    }
}

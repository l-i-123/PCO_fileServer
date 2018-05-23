#include "requestdispatcherthread.h"
#include "sendrequestthread.h"
#include <QVector>

RequestDispatcherThread::RequestDispatcherThread(AbstractBuffer<Request>* requestsBuffer, AbstractBuffer<Response>* responsesBuffer, bool hasDebugLog){
    this->requestsBuffer = requestsBuffer;
    this->responsesBuffer = responsesBuffer;
    this->hasDebugLog = hasDebugLog;
}

void RequestDispatcherThread::run(){

    while(true){
        SendRequestThread* newThread;
        request = requestsBuffer->get();
        newThread = new SendRequestThread(request, responsesBuffer, hasDebugLog);
        connect(newThread, &SendRequestThread::finished, newThread, &QObject::deleteLater);
        newThread->start();
    }

}

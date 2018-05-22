#include "requestdispatcherthread.h"
#include "sendrequestthread.h"
#include <QVector>

RequestDispatcherThread::RequestDispatcherThread(AbstractBuffer<Request>* requestsBuffer, AbstractBuffer<Response>* responsesBuffer, bool hasDebugLog){
    this->requestsBuffer = requestsBuffer;
    this->responsesBuffer = responsesBuffer;
    this->hasDebugLog = hasDebugLog;
}

void RequestDispatcherThread::run(){
    //int nbHeart = QThread::idealThreadCount();
    SendRequestThread* send;
    while(true){
        request = requestsBuffer->get();
        send = new SendRequestThread(request, responsesBuffer, hasDebugLog);
        send->start();
        //connect(SendRequestThread, &SendRequestThread::finished,SendRequestThread, QObject::deleteLater());
    }

}

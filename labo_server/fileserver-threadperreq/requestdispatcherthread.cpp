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
    while(true){
        printf("attent d'une valeur dans le buffer\n");
        request = requestsBuffer->get();
        printf("Une valeur est arrive dans le buffer\n");
        new SendRequestThread(request, responsesBuffer, hasDebugLog);
        //connect(SendRequestThread, &SendRequestThread::finished,SendRequestThread, QObject::deleteLater());
    }

}

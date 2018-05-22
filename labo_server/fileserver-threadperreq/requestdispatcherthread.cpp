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
    SendRequestThread* newThread;
    QVector<SendRequestThread*>* threadArray = new QVector<SendRequestThread*>;

    while(true){

        for(int i = 0; i < threadArray->size(); i++){
            if(threadArray->at(i)->wait(1)){
                threadArray->removeAt(i);
            }
        }

        request = requestsBuffer->get();
        newThread = new SendRequestThread(request, responsesBuffer, hasDebugLog);
        threadArray->push_front(newThread);
        newThread->start();
        //connect(newThread, &SendRequestThread::finished,QObject, QObject::deleteLater());
    }

}

#include "requestdispatcherthread.h"
#include "sendrequestthread.h"
#include <QVector>

RequestDispatcherThread::RequestDispatcherThread(AbstractBuffer<Request>* requestsBuffer, AbstractBuffer<Response>* responsesBuffer){
    this->requestsBuffer = requestsBuffer;
    this->responsesBuffer = responsesBuffer;
}

void RequestDispatcherThread::run(){
    //int nbHeart = QThread::idealThreadCount();
    while(true){
        request = requestsBuffer->get();

        //connect(SendRequestThread, &SendRequestThread::finished,SendRequestThread, QObject::deleteLater());
    }

}

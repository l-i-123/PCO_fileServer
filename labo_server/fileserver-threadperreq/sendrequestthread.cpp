#include "sendrequestthread.h"


SendRequestThread::SendRequestThread(Request request, MesaBuffer<Response>* responsesBuffer, bool hasDebugLog): request(request), responsesBuffer(responsesBuffer), hasDebugLog(hasDebugLog)
{
    this->responsesBuffer = responsesBuffer;
}

void SendRequestThread::run(){
    reqHandler = new RequestHandler(request, hasDebugLog);
    response = reqHandler->handle();
}

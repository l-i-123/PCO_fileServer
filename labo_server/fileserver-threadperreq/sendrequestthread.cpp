#include "sendrequestthread.h"


SendRequestThread::SendRequestThread(Request request, AbstractBuffer<Response>* responsesBuffer, bool hasDebugLog): request(request), responsesBuffer(responsesBuffer), hasDebugLog(hasDebugLog)
{
}

void SendRequestThread::run(){
    reqHandler = new RequestHandler(request, hasDebugLog);
    response = reqHandler->handle();
}

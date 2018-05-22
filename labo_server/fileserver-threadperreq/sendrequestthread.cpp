#include "sendrequestthread.h"
#include <QDebug>

SendRequestThread::SendRequestThread(Request request, AbstractBuffer<Response>* responsesBuffer, bool hasDebugLog): request(request), responsesBuffer(responsesBuffer), hasDebugLog(hasDebugLog)
{
}

void SendRequestThread::run(){
    if (hasDebugLog)
        qDebug() << "Envoie de requete...";
    reqHandler = new RequestHandler(request, hasDebugLog);
    response = reqHandler->handle();
    responsesBuffer->put(response);
}

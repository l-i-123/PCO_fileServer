/**
 * Description:     Class which sends the requests to the server and
 *                  then add the response in the buffer responses.
 * Name of file:    sendrequestthread.h
 * Authors:         NDjoli Elie
 *                  Silva Miguel
 * Date:            16.05.2018
 */
#include "sendrequestthread.h"
#include <QDebug>

SendRequestThread::SendRequestThread(Request request, AbstractBuffer<Response>* responsesBuffer, bool hasDebugLog): request(request), responsesBuffer(responsesBuffer), hasDebugLog(hasDebugLog)
{
}

void SendRequestThread::run(){
    if (hasDebugLog)
        qDebug() << "Envoie de requete...";
    /* Make request to the server */
    reqHandler = new RequestHandler(request, hasDebugLog);
    response = reqHandler->handle();
    /* Add the response of the server in the buffer response */
    responsesBuffer->put(response);
}

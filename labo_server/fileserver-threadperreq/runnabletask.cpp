/**
 * Description:     Class RunnableTask: The class RunnableTask
 *                  inherites from the class Runnable. Do the request to the
 *                  server and put the response in the buffer response.
 * Name of file:    runnabletask.h
 * Authors:         NDjoli Elie
 *                  Silva Miguel
 * Date:            30.05.2018
 */

#include "runnabletask.h"
#include "response.h"
#include "request.h"

RunnableTask::RunnableTask(Request request, AbstractBuffer<Response>* responsesBuffer, QString myId, bool hasDebugLog):request(request), responsesBuffer(responsesBuffer), hasDebugLog(hasDebugLog), myId(myId){}


void RunnableTask::run(){
    //création d'un nouveau request handler
    reqHandler = new RequestHandler(request, hasDebugLog);

    //Réception de la réponse
    Response response = reqHandler->handle();

    //Envoie de la réponse de la requête dans le response buffer
    responsesBuffer->put(response);
}

QString RunnableTask::id(){
    return myId;
}

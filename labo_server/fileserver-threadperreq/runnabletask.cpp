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

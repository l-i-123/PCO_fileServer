#include "runnable.h"
#include "response.h"
#include "request.h"

Runnable::Runnable(Request request, AbstractBuffer<Response>* responsesBuffer, QString myId, bool hasDebugLog):request(request), responsesBuffer(responsesBuffer), hasDebugLog(hasDebugLog), myId(myId){}


void Runnable::run(){
    //création d'un nouveau request handler
    reqHandler = new RequestHandler(request, hasDebugLog);

    //Réception de la réponse
    Response response = reqHandler->handle();

    //Envoie de la réponse de la requête dans le response buffer
    responsesBuffer->put(response);
}

Runnable::~Runnable(){
    delete reqHandler;
}

QString Runnable::id(){
    return myId;
}


#include "runnable.h"
#include "response.h"
#include "request.h"

Runnable::Runnable(Request request, AbstractBuffer<Response>* responsesBuffer, QString myId, bool hasDebugLog):request(request), responsesBuffer(responsesBuffer), hasDebugLog(hasDebugLog), myId(myId){}
Runnable::Runnable(){

}

void Runnable::run(){
    reqHandler = new RequestHandler(request, hasDebugLog);
    Response response = reqHandler->handle();
    responsesBuffer->put(response);
}

Runnable::~Runnable(){
    delete reqHandler;
}

QString Runnable::id(){
    return myId;
}


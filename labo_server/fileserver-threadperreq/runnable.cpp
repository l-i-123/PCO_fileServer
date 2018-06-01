#include "runnable.h"
#include "requesthandler.h"
#include "response.h"
#include "request.h"


Runnable::Runnable(Request request, AbstractBuffer<Response>* responsesBuffer, int myId, bool hasDebugLog):request(request), responsesBuffer(responsesBuffer), myId(myId), hasDebugLog(hasDebugLog){

}

void Runnable::run(){
    RequestHandler* reqHandler = new RequestHandler(request, hasDebugLog);
    Response response = reqHandler->handle();
    responsesBuffer->put(response);
}

QString Runnable::id(){
    return QString::number(myId);
}

#include "runnableTask.h"
#include "requesthandler.h"
#include "response.h"


RunnableTask::RunnableTask(Request request, AbstractBuffer<Response>* responsesBuffer, int myId, bool hasDebugLog):request(request), responsesBuffer(responsesBuffer), myId(myId), hasDebugLog(hasDebugLog){

}

RunnableTask::~RunnableTask(){

}

void RunnableTask::run(){
    RequestHandler* reqHandler = new RequestHandler(request, hasDebugLog);
    Response response = reqHandler->handle();
    responsesBuffer->put(response);
}

QString RunnableTask::id(){

}

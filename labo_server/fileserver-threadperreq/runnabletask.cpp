#include "runnabletask.h"

RunnableTask::RunnableTask()
{

}

RunnableTask::RunnableTask(Request request, AbstractBuffer<Response>* responsesBuffer, QString myId, bool hasDebugLog):request(request), responsesBuffer(responsesBuffer), hasDebugLog(hasDebugLog), myId(myId){}

void RunnableTask::run(){
    reqHandler = new RequestHandler(request, hasDebugLog);
    Response response = reqHandler->handle();
    responsesBuffer->put(response);
}

QString RunnableTask::id(){
    return myId;
}

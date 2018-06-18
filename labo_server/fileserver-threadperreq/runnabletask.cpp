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
#include "option.h"
#include "readerwritercache.h"
#include "readerwriterlock.h"

RunnableTask::RunnableTask(Request request, AbstractBuffer<Response>* responsesBuffer, QString myId, ReaderWriterCache* cache, bool hasDebugLog):request(request), responsesBuffer(responsesBuffer), hasDebugLog(hasDebugLog), myId(myId), cache(cache){}


void RunnableTask::run(){

    Response response ;

    Option<Response> cachedResponse = cache->tryGetCachedResponse(request);

    if(cachedResponse.hasValue()){
        response = cachedResponse.value();
    }
    else{
        //création d'un nouveau request handler
        reqHandler = new RequestHandler(request, hasDebugLog);

        //Réception de la réponse
        response = reqHandler->handle();

        cache->putResponse(response);
    }
    //Envoie de la réponse de la requête dans le response buffer
    responsesBuffer->put(response);

}

QString RunnableTask::id(){
    return myId;
}

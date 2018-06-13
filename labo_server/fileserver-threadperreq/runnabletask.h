/**
 * Description:     Prototype of class RunnableTask. The class RunnableTask
 *                  inherites from the class Runnable. Do the request to the
 *                  server and put the response in the buffer response.
 * Name of file:    runnabletask.h
 * Authors:         NDjoli Elie
 *                  Silva Miguel
 * Date:            30.05.2018
 */

#ifndef RUNNABLETASK_H
#define RUNNABLETASK_H
#include <QString>
#include "request.h"
#include "response.h"
#include "abstractbuffer.h"
#include "requesthandler.h"
#include "runnable.h"
#include "readerwritercache.h"

class RunnableTask: public Runnable
{
private:
    Request request;
    /* Pointer to the buffer of the responses */
    AbstractBuffer<Response>* responsesBuffer;
    bool hasDebugLog;
    RequestHandler* reqHandler;
    QString myId;
    ReaderWriterCache* cache;
public:

    /**
     * Construtor
     * @brief RunnableTask
     * @param request
     * @param responsesBuffer
     * @param myId
     * @param hasDebugLog
     */
    RunnableTask(Request request, AbstractBuffer<Response>* responsesBuffer, QString myId, ReaderWriterCache* cache, bool hasDebugLog);

    /**
     * Method doing the request to the server. Then put the response
     * in the response buffer.
     * @brief run
     */
    void run();

    /**
     * Method returns the id of the Runnable as a QString
     * @brief id
     * @return
     */
    QString id();
};

#endif // RUNNABLETASK_H

#ifndef RUNNABLE_H
#define RUNNABLE_H
#include <QString>
#include "request.h"
#include "response.h"
#include "abstractbuffer.h"
#include "QObject"

class Runnable : public QObject
{
    Q_OBJECT
private:
    Request request;
    AbstractBuffer<Response>* responsesBuffer;
    bool hasDebugLog;
public:
    Runnable();
    Runnable(Request request, AbstractBuffer<Response>* responsesBuffer, int myId, bool hasDebugLog);
    Runnable(Request request, AbstractBuffer<Response>* responsesBuffer, bool hasDebugLog);
    ~Runnable(){

    }
    void run();

    QString id();
    int myId;
};

#endif // RUNNABLE_H

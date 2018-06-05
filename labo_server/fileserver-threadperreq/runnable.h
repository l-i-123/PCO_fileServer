#ifndef RUNNABLE_H
#define RUNNABLE_H
#include <QString>
#include "request.h"
#include "response.h"
#include "abstractbuffer.h"
#include <QObject>
#include "requesthandler.h"

class Runnable : public QObject
{
    Q_OBJECT
private:
    Request request;
    AbstractBuffer<Response>* responsesBuffer;
    bool hasDebugLog;
    RequestHandler* reqHandler;
    QString myId;
public:
    Runnable();
    Runnable(Request request, AbstractBuffer<Response>* responsesBuffer, QString myId, bool hasDebugLog);
    ~Runnable();

    void run();

    QString id();
};

#endif // RUNNABLE_H

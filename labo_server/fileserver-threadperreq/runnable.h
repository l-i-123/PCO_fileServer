#ifndef RUNNABLE_H
#define RUNNABLE_H
#include <QString>
#include "request.h"
#include "response.h"
#include "abstractbuffer.h"

class Runnable
{
public:
    virtual ~Runnable(){

    }
    virtual void run() = 0;
    virtual QString id() = 0;
};

#endif // RUNNABLE_H

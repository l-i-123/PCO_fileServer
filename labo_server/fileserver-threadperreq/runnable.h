#ifndef RUNNABLE_H
#define RUNNABLE_H

#include <QString>

class Runnable
{
public:
    //virtual ~Runnable() = 0;

    virtual QString id() = 0;

    virtual void run() = 0;
};

#endif // RUNNABLE_H

/**
 * Description:     Prototype of class Runnable. The class RunnableTask
 *                  inherites from it.
 * Name of file:    runnable.h
 * Authors:         NDjoli Elie
 *                  Silva Miguel
 * Date:            30.05.2018
 */

#ifndef RUNNABLE_H
#define RUNNABLE_H

#include <QString>

class Runnable
{
public:
    //virtual ~Runnable() = 0;

    /**
     * Method implemented in RunnableTask.cpp
     * @brief id
     * @return
     */
    virtual QString id() = 0;

    /**
     * Method implemented in RunnableTask.cpp
     * @brief run
     */
    virtual void run() = 0;
};

#endif // RUNNABLE_H

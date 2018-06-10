/**
 * Description:     Prototype of class ThreadPool. This class has the methods
 *                  void put(Runnable*) and Runnable* get(void) to add or remove
 *                  the Runnable objects from the queue. When the runnable is
 *                  removed, it is attached to a thread available in the pool.
 *                  The threads are created when they are needed until the max
 *                  capacity of the pool is reached.
 *                  There is an internal class too named WorkerThread. The
 *                  WorkerThread objects are the thread used to be attached to
 *                  the Runnable objects. The threads are not destroyed. They
 *                  are reused. The method start of WorkerThread has a loop
 *                  while to check when a runnable is added in the QVector
 *                  runnableVector.
 *
 * Name of file:    threadpool.h
 * Authors:         NDjoli Elie
 *                  Silva Miguel
 * Date:            30.05.2018
 */

#include "runnable.h"
#include <QThread>
#include <QVector>
#include <QMutex>
#include "request.h"
#include "hoaremonitor.h"


#ifndef THREADPOOL_H
#define THREADPOOL_H

class ThreadPool : public HoareMonitor
{
    Q_OBJECT

public:

    /**
     * Constructor
     * @brief ThreadPool
     * @param poolThreadCapacity
     * @param hasDebugLog
     */
    ThreadPool(int poolThreadCapacity, bool hasDebugLog);

    /**
     * Constructor
     * @brief ThreadPool
     * @param poolThreadCapacity
     */
    ThreadPool(int poolThreadCapacity);

    /**
     * Destructor
     */
    ~ThreadPool();

    /**
     * Method using the method put to add Runnable objects in the QVector runnableVector
     * and creating new WorkerThread when needed until the maximum
     * threads in the pool.
     * @brief start
     * @param runnable
     */
    void start(Runnable* runnable);

    /**
     * Method adding the Runnable objects in the QVector runnableVector.
     * @brief put
     * @param item
     */
    void put(Runnable* item);

    /**
     * Method remove a Runnable object from runnableVector and return it.
     * @brief get
     * @return
     */
    Runnable* get(void);
    int nbWaitingConso = 0;
    int nbWaitingProd = 0;
    QMutex mutex;

    void ThreadPool::lockMutex(void);

    void ThreadPool::unlockMutex(void);


    /**
     * This object is a thread. It is used to attach the Runnable objects
     * @brief The WorkerThread class
     */
    class WorkerThread: public QThread
    {
        friend ThreadPool;

    public:

        /**
         * Constructor
         * @brief WorkerThread
         * @param poolPointer
         */
        WorkerThread(ThreadPool* poolPointer);

        /**
         * Set a pointer to another runnable to the variable runnable.
         * @brief setNewRunnable
         * @param newRunnable
         */
        void setNewRunnable(Runnable* newRunnable);
        Runnable* runnable;

    private:

        ThreadPool* poolPointer;

    protected:

        /**
         * Method checking when a runnable is in the QVector
         * runnableVector. When there is one the thread launched
         * the method run() of the object RunnableTask. It makes
         * the request to the server.
         * @brief run
         */
        void run() Q_DECL_OVERRIDE;

    };



private:

    /* Maximum number of threads in the pool */
    int poolThreadCapacity;
    /* Number of threads created */
    unsigned int createdThread;
    /* Number of threads in used */
    unsigned int poolThreadUsed;
    /* QVector with all threads of the pool */
    QVector<WorkerThread*> threadsVector;
    /* QVector with the Runnable objects waiting
       the availability of a thread */
    QVector<Runnable*> runnableVector;
    bool hasDebugLog;
    /* Consumer condition variable */
    Condition waitConso;
    /* Producer condition variable */
    Condition waitProd;

};



#endif // THREADPOOL_H

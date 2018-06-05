#include "threadpool.h"
#include <QDebug>

//D:\HEIG-VD\Informatique\PCO\labo_server\labo_server\fileserver\shakespeare.txt

ThreadPool::ThreadPool(int poolThreadCapacity, bool hasDebugLog):poolThreadCapacity(poolThreadCapacity),poolThreadUsed(0), hasDebugLog(hasDebugLog)
{

}


void ThreadPool::start(Runnable* runnable){
    monitorIn();

    if (hasDebugLog) {
         qDebug() << "Nombre de thread dans le threadsVector: " << threadsVector.size();
     }

    runnableVector.push_front(runnable);

    //Si le nombre de thread utilisé est égal au nombre
    // de thread maximum
    if(poolThreadUsed == poolThreadCapacity){
        wait(waitCond);
    }
    //si le nombre de thread utilisé est égal au nombre de
    // thread créé
    else if(poolThreadUsed == threadsVector.size()){
        Worker* newWorker = new Worker(runnableVector.back());
        runnableVector.pop_back();

        threadsVector.push_front(newWorker);
        connect(newWorker, &Worker::runnableEnd, this, &ThreadPool::runnableFinished);

        threadsVector.front()->start();
        poolThreadUsed++;
    }
    else{
        bool freeWorkerFind = false;
        int count = 0;
        while(freeWorkerFind == false && count < threadsVector.size()){
            if(threadsVector.at(count)->isFinished()){
                threadsVector.at(count)->setNewRunnable(runnableVector.back());
                threadsVector.at(count)->start();

                runnableVector.pop_back();
                poolThreadUsed++;

                freeWorkerFind = true;
            }
            count++;
        }
    }

    monitorOut();

}

void ThreadPool::runnableFinished(QString id){
    poolThreadUsed--;
    signal(waitCond);
}

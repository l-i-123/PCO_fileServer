/**
 * Description:     Class ThreadPool: This class has the methods
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
 * Name of file:    threadpool.cpp
 * Authors:         NDjoli Elie
 *                  Silva Miguel
 * Date:            30.05.2018
 */

#include "threadpool.h"
#include <QDebug>

ThreadPool::ThreadPool(int poolThreadCapacity, bool hasDebugLog):poolThreadCapacity(poolThreadCapacity),createdThread(0), hasDebugLog(hasDebugLog), poolThreadUsed(0){
    mutex = new QSemaphore(1);
}

ThreadPool::ThreadPool(int poolThreadCapacity):poolThreadCapacity(poolThreadCapacity),createdThread(0), poolThreadUsed(0) {
    mutex = new QSemaphore(1);
}

ThreadPool::WorkerThread::WorkerThread(ThreadPool* poolPointer):poolPointer(poolPointer){

    poolThreadUsed = &poolPointer->poolThreadUsed;
}

void ThreadPool::WorkerThread::run(){

    //Lancement du runnable
    while(true){

            runnable = poolPointer->get();

            poolPointer->mutex->acquire();
            (*poolThreadUsed)++;
            poolPointer->mutex->release();

            runnable->run();


            poolPointer->mutex->acquire();
            (*poolThreadUsed)--;
            poolPointer->mutex->release();
    }
}

ThreadPool::~ThreadPool(){

    //Destruction de tous les threads
    for(int i = 0; i < threadsVector.size(); i++){
        threadsVector.at(i)->terminate();
        threadsVector.at(i)->wait();
        threadsVector.at(i)->deleteLater();
    }

    delete mutex;
}

void ThreadPool::put(Runnable* item) {

    monitorIn();

    runnableVector.push_front(item);

    /* Vérifie si un consommateur est disponible ou non */
    /*
    if (nbWaitingConso > 0) {
        nbWaitingConso -= 1;
        signal(waitConso);
    }
    */
    signal(waitConso);

    monitorOut();
}



Runnable* ThreadPool::get(void) {

    Runnable* item;

    monitorIn();

    /* Vérifie s'il y a un objet Runnable en attente dans le QVector.
       Se met en attente s'il y en a pas. */
    if (runnableVector.empty()) {
        //nbWaitingConso += 1;
        wait(waitConso);
    }

    item = runnableVector.back();
    runnableVector.pop_back();

    monitorOut();

    return item;
}





void ThreadPool::start(Runnable* runnable){
    //cet affichage permet de voir le vecteur de thread grandir en fonction du nombre de
    //requête lancé en paralelle
    //if (hasDebugLog) {
    //   qDebug() << "Nombre de thread dans le threadsVector: " << threadsVector.size();
    //}

    put(runnable);

    // Vérifie si le nombre the thread est au maximum et si le nombre de thread
    // créé et le même que le nombre de thread utilisé en ce moment
    mutex->acquire();
    qDebug() << "Nombre de thread dans le threadsVector: " << threadsVector.size();
    qDebug() << "CreatedThread : " << createdThread;
    qDebug() << "poolThreadUsed: " << poolThreadUsed;
    if((threadsVector.size() < poolThreadCapacity) && (createdThread == poolThreadUsed)){
    //if(threadsVector.size() < poolThreadCapacity){
        //Création d'un nouveau Worker
        WorkerThread* newWorker = new WorkerThread(this);

        threadsVector.push_front(newWorker);
        threadsVector.front()->start();
        createdThread++;
    }
    mutex->release();

}














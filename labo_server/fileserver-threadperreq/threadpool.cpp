#include "threadpool.h"
#include <QDebug>

ThreadPool::ThreadPool(int poolThreadCapacity, bool hasDebugLog):poolThreadCapacity(poolThreadCapacity),poolThreadUsed(0), hasDebugLog(hasDebugLog)
{

}

ThreadPool::ThreadPool(int poolThreadCapacity):poolThreadCapacity(poolThreadCapacity),poolThreadUsed(0){

}

ThreadPool::WorkerThread::WorkerThread(ThreadPool* poolPointer):poolPointer(poolPointer)
{

}

void ThreadPool::WorkerThread::run(){
    //Lancement du runnable
    while(true){
        runnable = poolPointer->get();
        runnable->run();
    }
}

ThreadPool::~ThreadPool(){

    //Déstruction de tous les threads
    for(int i = 0; i < threadsVector.size(); i++){
        threadsVector.at(i)->terminate();
        threadsVector.at(i)->wait();
        threadsVector.at(i)->deleteLater();
    }

}

void ThreadPool::put(Runnable* item) {
    monitorIn();

    runnableVector.push_front(item);

    if (nbWaitingConso > 0) {
        nbWaitingConso -= 1;
        signal(waitConso);
    }

    monitorOut();
}

Runnable* ThreadPool::get(void) {
    Runnable* item;
    monitorIn();

    poolThreadUsed++;

    if (runnableVector.empty()) {
        nbWaitingConso += 1;
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
    //si le nombre de thread utilisé est égal au nombre de
    // thread créé cela signifie qu'il faut en créer de nouveau
    if(poolThreadUsed < poolThreadCapacity){
        //Création d'un nouveau Worker
        WorkerThread* newWorker = new WorkerThread(this);

        threadsVector.push_front(newWorker);

        threadsVector.front()->start();
        poolThreadUsed++;
    }

}

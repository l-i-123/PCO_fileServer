#include "threadpool.h"
#include <QDebug>

ThreadPool::ThreadPool(int poolThreadCapacity, bool hasDebugLog):poolThreadCapacity(poolThreadCapacity),poolThreadUsed(0), hasDebugLog(hasDebugLog)
{

}

ThreadPool::ThreadPool(int poolThreadCapacity):poolThreadCapacity(poolThreadCapacity),poolThreadUsed(0){

}

ThreadPool::~ThreadPool(){

    for(int i = 0; i < threadsVector.size(); i++){
        threadsVector.at(i)->terminate();
        threadsVector.at(i)->wait();
        threadsVector.at(i)->deleteLater();
    }

    for(int i = 0; i < runnableVector.size(); i++){
        runnableVector.at(i)->deleteLater();
    }

}

void ThreadPool::start(Runnable* runnable){
    monitorIn();

    //cet affichage permet de voir le vecteur de thread grandir en fonction du nombre de
    //requête lancé en paralelle
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
    // thread créé cela signifie qu'il faut en créer de nouveau
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
        //Recherche du premier thread libre
        while(freeWorkerFind == false && count < threadsVector.size()){
            if(threadsVector.at(count)->isFinished()){
                threadsVector.at(count)->setNewRunnable(runnableVector.back());
                runnableVector.pop_back();

                threadsVector.at(count)->start();

                poolThreadUsed++;
                freeWorkerFind = true;
            }
            count++;
        }
    }

    monitorOut();

}

//Méthode appelé à la fin de chaque worker(runnable)
void ThreadPool::runnableFinished(){
    monitorIn();

    poolThreadUsed--;
    signal(waitCond);

    monitorOut();
}

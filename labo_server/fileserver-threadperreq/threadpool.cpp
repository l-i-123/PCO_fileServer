#include "threadpool.h"

ThreadPool::ThreadPool(int maxThreadCount):maxThreadCount(maxThreadCount)
{
    currentThreadCount = 0;
    freeThread.fill(true, maxThreadCount);
}


void ThreadPool::start(Runnable* runnable){

    monitorIn();


    threadsVector.push_front(new QThread());
    runnableVector.push_front(runnable);

    if(currentThreadCount >= maxThreadCount){
        wait(allThreadBusy);
    }

    if(currentThreadCount == threadsVector.size() && threadsVector.size() < maxThreadCount){
        Worker* worker = new Worker(runnable);

        //Peux-être pas nécessaire
        threadsVector.push_back(new Worker(runnable));

        //Communication entre le worker et le threadpool
        connect(worker, SIGNAL(runnableEnd(int)), this, SLOT(handleThreadEnd(int)));

        //Géré de nouvelle connection afin d'attribuer de nouveaux runnable aux worker libre
        //Ce sera probablement quelque chose du style
        //connect(this, SIGNAL(newRunnable(Runnable)), threadsVector.at(i), SLOT(newRunnable(Runnable)));
        //La méthode new runnable du threadPool devra géré la concurrence entre les Runnable disponible et les thread en demande


        currentThreadCount++;
        freeThread.at(currentThreadCount - 1) = false;
    }



    monitorOut();
}

//Signal reçu lorsque l'execution d'un runnable est terminé
//number retourne le numéro du thread concerné
void ThreadPool::handleThreadEnd(int number){
    monitorIn();

    freeThread.at(number - 1) = true;
    currentThreadCount--;

    monitorOut();
}

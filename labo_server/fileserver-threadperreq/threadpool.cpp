#include "threadpool.h"

ThreadPool::ThreadPool(int maxThreadCount):maxThreadCount(maxThreadCount)
{
    threadBusyCount = 0;
    threadCreateCount = 0;
    freeThread.fill(true, maxThreadCount);
}


void ThreadPool::start(Runnable* runnable){


    //Cas ou tous les thread ne son pas encore créé
    if(threadBusyCount == threadCreateCount && threadsVector.size() < maxThreadCount){
        Worker* worker = new Worker(runnable, threadCreateCount++);

        printf("NEW THREAD!!!\n");

        //Peux-être pas nécessaire
        threadsVector.push_back(worker);

        //Communication entre le worker et le threadpool
        connect(worker, SIGNAL(runnableEnd(int)), this, SLOT(handleThreadEnd(int)));

        //Géré de nouvelle connection afin d'attribuer de nouveaux runnable aux worker libre
        //Ce sera probablement quelque chose du style
        connect(this, SIGNAL(newRunnable(Runnable*)), worker, SLOT(newRunnable(Runnable*)));
        //La méthode new runnable du threadPool devra géré la concurrence entre les Runnable disponible et les thread en demande

        worker->start();

        threadBusyCount++;
        threadCreateCount++;
    }
    else{
        runnableVector.push_front(runnable);

        signal(emptyRunnableVector);
    }

}

//Signal reçu lorsque l'execution d'un runnable est terminé
//number retourne le numéro du thread concerné

//Cette fonction est appelé à la fin d'un thread et lui renvoie un nouveau runnable à traiter
void ThreadPool::handleThreadEnd(int number){
    monitorIn();

    printf("HANDLE_THREAD_END RECU!!!\n");

    //Attente si tous les thread son occupé
    if(runnableVector.size() == 0){
        wait(emptyRunnableVector);
    }

    Runnable* run = runnableVector.back();
    runnableVector.pop_back();

    run->id() = number;
    newRunnable(run);
    runnableVector.pop_back();
    //Il faut encore gérer le signal allThreadBusy


    monitorOut();
}

#include "threadpool.h"

ThreadPool::ThreadPool(int maxThreadCount):poolThreadCapacity(maxThreadCount),poolThreadUsed(0)
{
    poolThreadTab = new QVector<Runnable*>;
    for(int i = 0; i < poolThreadCapacity; ++i){
        poolThreadTab->append(new Runnable());
        poolThreadTab->at(i)->myId = i;
        threadAvailable.push_back(true);
    }
}


void ThreadPool::start(Runnable* runnable){
    monitorIn();
    Runnable *temp;

    if(poolThreadUsed == poolThreadCapacity){
        wait(waitCond);
    }

    poolThreadUsed++;
    int i = 0;
    for(; i < poolThreadCapacity; ++i){
        if(threadAvailable.at(i)){
            poolThreadTab->at(i) = runnable;
            threadAvailable.at(i) = false;
        }
    }

    connect(poolThreadTab->at(i), &Runnable::finished, poolThreadTab->at(i), &QThread::wait)

    poolThreadTab->at(i)->start();
   // if()
/*
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
*/
    monitorOut();

}

//Signal reçu lorsque l'execution d'un runnable est terminé
//number retourne le numéro du thread concerné

//Cette fonction est appelé à la fin d'un thread et lui renvoie un nouveau runnable à traiter
void ThreadPool::handleThreadEnd(int number){
    monitorIn();

    /*
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

*/

    monitorOut();
}

void ThreadPool::run(Runnable* runnable){

    while(true){
        if(waitRunnable == false){
            printf("NEW WORKER RUN\n");
            runnable->run();
            runnableEnd(threadId); // send signal
            waitRunnable = true;
        }
    }
}

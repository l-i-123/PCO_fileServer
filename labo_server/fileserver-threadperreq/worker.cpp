#include "worker.h"

Worker::Worker(RunnableTask* runnable):runnable(runnable)
{

}

void Worker::run(){
    //Lancement du runnable
    runnable->run();

    //Lorsque le runnable est fini un message est envoyé à la classe ThreadPool
    emit runnableEnd();
}

//La méthode setNewRunnble permet au worker de recevoir de nouveau runnable
void Worker::setNewRunnable(RunnableTask* newRunnable){
    runnable = newRunnable;
}

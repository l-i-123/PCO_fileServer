#include "worker.h"

Worker::Worker(Runnable* runnable):runnable(runnable)
{

}

void Worker::run(){
    printf("worker start\n");
    runnable->run();
    emit runnableEnd(runnable->id());
}


void Worker::setNewRunnable(Runnable* newRunnable){
    runnable = newRunnable;
}

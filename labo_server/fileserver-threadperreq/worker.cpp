#include "worker.h"

Worker::Worker(Runnable* runnable):runnable(runnable)
{

}

void Worker::run(){
    printf("worker start\n");
    runnable->run();
    emit runnableEnd();
}

void Worker::setNewRunnable(Runnable* newRunnable){
    runnable = newRunnable;
}

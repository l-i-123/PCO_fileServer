#include "worker.h"

Worker::Worker(Runnable* runnable, int threadId):runnable(runnable), threadId(threadId)
{

}

void Worker::run(){

    while(true){
        if(waitRunnable == false){
            runnable->run();
            runnableEnd(threadId); // send signal
            waitRunnable = true;
        }
    }
}

void Worker::newRunnable(Runnable* runnable){
    if(runnable->id() == threadId){
        this->runnable = runnable;
        waitRunnable = false;
    }
}

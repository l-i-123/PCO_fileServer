#include "worker.h"

Worker::Worker(Runnable* runnable):runnable(runnable)
{

}

void Worker::run(){

    while(true){
        runnable->run();
        runnableEnd((int)1); // send signal
    }
}

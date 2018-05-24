/**
 * Description:     Class implementing a Mesa monitor. The two methods of the class
 *                  AbstractBuffer are implemented here.
 * Name of file:    mesabuffer.h
 * Authors:         NDjoli Elie
 *                  Silva Miguel
 * Date:            16.05.2018
 */

#ifndef MESABUFFER_H
#define MESABUFFER_H

#include "abstractbuffer.h"
#include <QMutex>
#include <QVector>
#include <QWaitCondition>

template<typename T>
class MesaBuffer : public AbstractBuffer<T>
{
public:
    MesaBuffer(){}

    /* Add a request (thread) in the request buffer */
    void put(T item){
        mutex->lock();//beginning of the critical section

        /* Check and loop if there are 20 or more threads in the buffer */
        while(buffer.size() > 20){
            isFree.wait(mutex);
        }

        buffer.push_front(item);
        /* "Réveille" an item in waiting status */
        isFull.wakeOne();

        mutex->unlock(); // end of the critical section
    }

    /* Return a request (thread) of the request buffer */
    T get(){
        T result;
        mutex->lock(); //beginning of the critical section

        /* Check and loop if the buffer is empty */
        while(buffer.isEmpty()){
            isFull.wait(mutex);
        }
        result = buffer.last();
        buffer.pop_back();

        mutex->unlock(); // end of the critical section
        isFree.wakeOne();
        return result;
    }

    bool tryPut(T item){
        mutex->lock();
        if(buffer.size() > 20){
            buffer.push_front(item);
            isFull.wakeOne();
        }
        else{
            mutex->unlock();
            return false;
        }

        mutex->unlock();
        return true;
    }

private:
    QVector<T> buffer;
    QMutex* mutex = new QMutex();
    QWaitCondition isFree, isFull;
};

#endif // BUFFER_H

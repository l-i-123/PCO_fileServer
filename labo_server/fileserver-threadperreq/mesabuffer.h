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

    void put(T item){
        mutex->lock();
        while(buffer.size() > 20){
            isFree.wait(mutex);
        }
        buffer.push_front(item);
        isFull.wakeOne();
        mutex->unlock();
    }

    T get(){
        T result;
        mutex->lock();
        while(buffer.isEmpty()){
            isFull.wait(mutex);
        }
        result = buffer.last();
        buffer.pop_back();

        mutex->unlock();
        isFree.wakeOne();
        return result;
    }

private:
    QVector<T> buffer;
    QMutex* mutex = new QMutex();
    QWaitCondition isFree, isFull;
};

#endif // BUFFER_H

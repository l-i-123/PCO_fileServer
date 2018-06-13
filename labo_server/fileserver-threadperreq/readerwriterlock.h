#ifndef READERWRITERLOCK_H
#define READERWRITERLOCK_H

#include "QSemaphore"

class ReaderWriterLock
{

public:
    ReaderWriterLock();

    void lockReading();
    void lockWriting();
    void unlockReading();
    void unlockWriting();

protected:
    QSemaphore mutexReaders;
    QSemaphore mutexWriters;
    QSemaphore writer;
    QSemaphore reader;
    QSemaphore mutex;
    int nbReaders, nbWriters;
};

#endif // READERWRITERLOCK_H

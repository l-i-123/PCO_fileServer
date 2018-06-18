/**
 * Description:     La class ReaderWriterLock implémente un algorithme de lecteur/redacteur
 * Name of file:    readerwriterlock.h
 * Authors:         NDjoli Elie
 *                  Silva Miguel
 * Date:            18.06.2018
 */


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

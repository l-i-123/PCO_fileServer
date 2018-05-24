/**
 * Description:     Prototype of a generic class to create a buffer
 * Name of file:    abstractbuffer.h
 * Authors:         NDjoli Elie
 *                  Silva Miguel
 * Date:            16.05.2018
 */

#ifndef ABSTRACTBUFFER_H
#define ABSTRACTBUFFER_H

template<typename T>
class AbstractBuffer {
public:

    /**
     * Method to add a thread in the request buffer.
     * a request
     * @brief put
     * @param item
     */
    virtual void put(T item) = 0;

    /**
     * Method to get a thread of the request buffer
     * @brief get
     * @return
     */
    virtual T get() = 0;
    virtual bool tryPut(T item) = 0;
};

#endif // ABSTRACTBUFFER_H

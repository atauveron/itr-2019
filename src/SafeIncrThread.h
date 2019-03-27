/**
 * @file Thread.h
 * @brief Implementation of the Thread class
 */

// TODO UPDATE DOC

#ifndef SAFE_INCR_THREAD_INCLUDED
#define SAFE_INCR_THREAD_INCLUDED

#include "Thread.h"

/**
 * @brief A class that implements a Thread
 */
class SafeIncrThread : public Thread {

  private:
    /**
     * @brief A Chronometer object
     */
    volatile double *p_counter;
    /**
     * @brief A Chronometer object
     */
    unsigned int loops;
    Mutex *mutex;

  public:
    /**
     * @brief Default constructor
     * It is not required.
     */
    SafeIncrThread(volatile double *p_counter, unsigned int nLoops,
		   int schedPolicy, Mutex *mtx);

    SafeIncrThread(SafeIncrThread const &);

    ~SafeIncrThread();
    /**
     * @brief Default destructor
     * It is not required.
     */
    void run();
};

#endif
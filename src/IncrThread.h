/**
 * @file Thread.h
 * @brief Implementation of the Thread class
 */

// TODO UPDATE DOC

#ifndef INCR_THREAD_INCLUDED
#define INCR_THREAD_INCLUDED

#include "Thread.h"

/**
 * @brief A class that implements a Thread
 */
class IncrThread : public Thread {

  private:
    /**
     * @brief A Chronometer object
     */
    volatile double *p_counter;
    /**
     * @brief A Chronometer object
     */
    unsigned int loops;

  public:
    /**
     * @brief Default constructor
     * It is not required.
     */
    IncrThread(volatile double *p_counter, unsigned int nLoops,
	       int schedPolicy);
    /**
     * @brief Default destructor
     * It is not required.
     */
    void run();
};

#endif
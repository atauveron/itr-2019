/**
 * @file PosixThread.h
 * @brief Implementation of the PosixThread class
 */

// TOFDO UPDATE DOC
#ifndef POSIX_THREAD_INCLUDED
#define POSIX_THREAD_INCLUDED

#include <exception>
#include <pthread.h>

#include "Mutex.h"

/**
 * @brief A class that implements a POSIX Thread
 */
class PosixThread {

  public:
    /**
     * @brief An exception class in case of wrong process acquiring
     */
    class Exception : std::exception {
      public:
	/**
	 * @brief Return a character string describing the error
	 */
	const char *what() const noexcept;
    };

  private:
    /**
     * @brief the id of the underlying Posix thread
     */
    pthread_t posixId;
    /**
     * @brief the attributes of the underlying Posix thread
     */
    pthread_attr_t posixAttr;

  private:
    static pthread_t INVALID_PTHREAD_;
    volatile static bool READY_;
    static Mutex MUTEX_;

  public:
    static pthread_t INVALID_PTHREAD();
    static void *dummyFunction(void *);
    /**
     * @brief Default constructor
     */
    PosixThread();
    /**
     * @brief Constructor from an existing pthread
     *
     * @param posixId the identifier of the pthread from which to construct the
     * object
     */
    PosixThread(pthread_t posixId);
    /**
     * @brief Destructor
     */
    ~PosixThread();
    /**
     * @brief Run a function in the thread
     *
     * @param threadFunc the function to run
     * @param threadArg the arguments for the function to run
     */
    void start(void *(*threadFunc)(void *), void *threadArg);
    /**
     * @brief Join a thread
     */
    void join();
    /**
     * @brief Join a thread (with a timeout)
     * If the timeout delay elapses before the thread joins, the thread id
     * killed.
     *
     * @param timeout_ms the timeout delay (in ms)
     * @return `true` if the thread was joined successfully, `false` otherwise
     */
    bool join(double timeout_ms);
    /**
     * @brief Set the scheduling policy of the thread
     *
     * @param schedPolicy the scheduling policy for the thread
     * @param priority the priority of the thread
     * @return `true` if the operation succeeds, `false` otherwise
     */
    bool setScheduling(int schedPolicy, int priority);
    /**
     * @brief Get the scheduling policy of the thread
     *
     * @param[out] p_schedPolicy the current scheduling policy for the thread
     * @param[out] p_priority the current priority of the thread
     * @return `true` if the operation succeeds, `false` otherwise
     */
    bool getScheduling(int *p_schedPolicy = nullptr,
		       int *p_priority = nullptr) const;
};

#endif
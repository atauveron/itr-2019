/**
 * @file Thread.h
 * @brief Implementation of the Thread class
 */

#ifndef THREAD_INCLUDED
#define THREAD_INCLUDED

#include "Chrono.h"
#include "PosixThread.h"

/**
 * @brief A class that implements a Thread
 */
class Thread : public PosixThread
{

	private:
		/**
		 * @brief A Chronometer object
		 */
		Chrono chrono;

	public:
		/**
		 * @brief Default constructor
		 * It is not required.
		 */
		Thread();

		/**
		 * @brief Default destructor
		 * It is not required.
		 */
		~Thread();

		/**
		 * @brief Start the thread with the call_run function
		 *
		 * @return the start time of the thread (converted to ms)
		 */
		void start();

		/**
		 * @brief Get the start time of the thread
		 *
		 * @return the start time of the thread (converted to ms)
		 */
		double startTime_ms();

		/**
		 * @brief Get the stop time of the thread
		 *
		 * @return the stop time of the thread (converted to ms)
		 */
		double stopTime_ms();

		/**
		 * @brief Get the execution time of the thread
		 *
		 * @return the execution time of the thread (in ms)
		 */
		double execTime_ms();

		/**
		 * @brief Pause the thread for a specified time
		 *
		 * @param delay_ms the duration for which to pause the thread
		 */
		static void sleep_ms(double delay_ms);

	protected:
		/**
		 * @brief The function executed by the thread. Needs to be implemented
		 * by child classes
		 */
		void virtual run() = 0;

	private:
		/**
		 * @brief The handler used by the thread to call the run function
		 *
		 * @param v_thread the data sent to handler containing the Thread
		 * instance calling the handler
		 */
		static void *call_run(void *v_thread);
};

#endif
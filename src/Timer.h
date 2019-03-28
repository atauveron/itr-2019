/**
 * @file Timer.h
 * @brief Implementation of the Timer class
 */

#ifndef TIMER_INCLUDED
#define TIMER_INCLUDED

#include <csignal>
#include <ctime>

/**
 * @brief A class that implements a timer
 */
class Timer
{
	protected:
		/**
		 * @brief The underlying Posix timer
		 */
		timer_t tid;

	public:
		/**
		 * @brief Default constructor
		 */
		Timer();

		/**
		 * @brief Default destructor
		 */
		virtual ~Timer();

		/**
		 * @brief Stop the timer
		 */
		void stop();

		/**
		 * @brief Start the timer
		 *
		 * @param duration_ms the timer delay (in ms)
		 */
		virtual void start(double duration_ms) = 0;

	protected:
		/**
		 * @brief The timer callback. Needs to be implemented by child classes
		 */
		virtual void callback() = 0;

	private:
		/**
		 * @brief The handler used by the timer to call the callback
		 *
		 * @param si the data sent to handler containing the Timer instance
		 * calling the handler
		 */
		static void call_callback(int, siginfo_t *si, void *);
};

#endif
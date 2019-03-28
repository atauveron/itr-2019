/**
 * @file Looper.h
 * @brief Implementation of the Looper class
 */

#ifndef LOOPER_INCLUDED
#define LOOPER_INCLUDED

#include <limits>

/**
 * @brief A class that implements a Looper system
 */
class Looper
{

	private:
		/**
		 * @brief Boolean to stop the Looper
		 */
		volatile bool doStop = false;

		/**
		 * @brief Number of loop executed
		 */
		double iLoop = 0;

	public:
		/**
		 * @brief Execute a number of loops
		 *
		 * @params nLoops The target number of loops the execute
		 * @return The actual number of loops executed
		 */
		double runLoops(double nLoops = std::numeric_limits<double>::max());

		/**
		 * @brief The handler used by the thread to call the runLoop function
		 *
		 * @param v_thread the data sent to handler containing the Looper
		 * instance calling the handler
		 */
		static void *call_loop(void *v_data);

		/**
		 * @brief Get the current number of Loops
		 */
		double getSamples();

		/**
		 * @brief Stop the execution of runLoops
		 */
		double stopLoop();
};

#endif
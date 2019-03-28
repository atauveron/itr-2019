/**
 * @file main_td4b.cpp
 * @brief Main file for tutorial question 4b
 */

// TODO UPDATE DOC

#include "SafeIncrThread.h"

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv)
{
		if (argc < 3)
		{
				std::cerr << "Usage: " << argv[0]
						  << " <nLoops> <nTasks> [schedPolicy]" << std::endl;
				return 1;
		}

		unsigned int nLoops		= std::stoul(argv[1]);
		unsigned int nTasks		= std::stoul(argv[2]);
		int			 policy		= 0;
		int			 priority   = 0;
		double volatile counter = 0;
		double mean_exec_time   = 0;
		Mutex  mutex;

		int schedPolicy(SCHED_OTHER);
		if (argc == 4)
		{
				if (!strcmp(argv[3], "SCHED_RR")) { schedPolicy = SCHED_RR; }
				else if (!strcmp(argv[3], "SCHED_FIFO"))
				{
						schedPolicy = SCHED_FIFO;
				}
		}

		// Thread
		std::vector<SafeIncrThread> incrementThreads(
			nTasks, SafeIncrThread(&counter, nLoops, schedPolicy, &mutex));

		incrementThreads[0].getScheduling(&policy, &priority);

		for (auto &thread : incrementThreads) { thread.start(); }

		for (auto &thread : incrementThreads)
		{
				thread.join();
				mean_exec_time += thread.execTime_ms();
		}

		std::cout << "Policy: " << policy << std::endl;

		std::cout << "Priority: " << priority << std::endl;

		std::cout << "Mean Execution time: " << mean_exec_time / (nTasks * 1000)
				  << "s" << std::endl;

		std::cout << "Counter: " << counter << std::endl;

		// Return
		return 0;
}
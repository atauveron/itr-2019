/**
 * @file main_td2a.cpp
 * @brief Main file for tutorial question 2a
 */

// TODO UPDATE DOC

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "IncrThread.h"

int main(int argc, char **argv) {
    if (argc < 3) {
	std::cerr << "Usage: " << argv[0] << " <nLoops> <nTasks> [schedPolicy]"
		  << std::endl;
	return 1;
    }
    unsigned int nLoops = std::stoul(argv[1]);
    unsigned int nTasks = std::stoul(argv[2]);
    int schedPolicy(SCHED_OTHER);
    if (argc == 4) {
	if (!strcmp(argv[3], "SCHED_RR")) {
	    schedPolicy = SCHED_RR;
	} else if (!strcmp(argv[3], "SCHED_FIFO")) {
	    schedPolicy = SCHED_FIFO;
	}
    }
    double volatile counter = 0;
    double mean_exec_time = 0;

    int policy = 0;
    int priority = 0;

    // Thread
    std::vector<IncrThread> incrementThreads(
	nTasks, IncrThread(&counter, nLoops, schedPolicy));

    for (auto &thread : incrementThreads) {
	thread.start();
    }

    incrementThreads[0].getScheduling(&policy, &priority);

    std::cout << "Policy: " << policy << std::endl;
    std::cout << "Priority: " << priority << std::endl;

    for (auto &thread : incrementThreads) {
	thread.join();
	mean_exec_time += thread.execTime_ms();
    }

    mean_exec_time /= nTasks;

    std::cout << "Mean Execution time: " << mean_exec_time / 1000 << "s"
	      << std::endl;
    std::cout << "Counter: " << counter << std::endl;

    // Return
    return 0;
}
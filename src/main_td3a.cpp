/**
 * @file main_td3a.cpp
 * @brief Main file for tutorial question 3a
 */

#include "Chrono.h"

#include <iostream>
#include <unistd.h>

int main()
{
		Chrono chrono;

		sleep(1);
		std::cout << "Time on chrono after 1 sec: " << chrono.lap()
				  << std::endl;

		sleep(2);
		std::cout << "Time on chrono after 3 sec: " << chrono.lap()
				  << std::endl;

		sleep(3);
		std::cout << "Time on chrono after 6 sec: " << chrono.lap()
				  << std::endl;

		sleep(4);
		std::cout << "Time on chrono after 10 sec: " << chrono.lap()
				  << std::endl;

		sleep(5);
		chrono.stop();
		std::cout << "Time on chrono after 15 sec: " << chrono.lap()
				  << std::endl;

		sleep(5);
		std::cout << "Time on chrono after 20 (5 sec pause) sec: "
				  << chrono.lap() << std::endl;
		chrono.restart();

		sleep(5);
		std::cout << "Time on chrono after 5 sec restart: " << chrono.lap()
				  << std::endl;

		chrono.stop();
		return 0;
}
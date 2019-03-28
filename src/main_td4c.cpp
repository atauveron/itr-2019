#include "Semaphore.h"
#include "SemaphoreConsumerThread.h"
#include "SemaphoreProducerThread.h"

#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

int main(int argc, char **argv)
{
		if (argc < 3)
		{
				std::cerr << "Usage: " << argv[0] << " <nCons> <nProd>\n";
				return 1;
		}
		unsigned int nCons	= std::stoul(argv[1]);
		unsigned int nProd	= std::stoul(argv[2]);
		unsigned int produced = 0;
		unsigned int consumed = 0;

		constexpr unsigned int nTokens(10);

		Semaphore semaphore;

		// Create the threads
		std::vector<SemaphoreConsumerThread> consThreads(
			nCons, SemaphoreConsumerThread(&semaphore));
		std::vector<SemaphoreProducerThread> prodThreads(
			nProd, SemaphoreProducerThread(&semaphore, nTokens));

		// Start the threads
		for (auto &consThread : consThreads) { consThread.start(); }
		for (auto &prodThread : prodThreads) { prodThread.start(); }

		// Join the threads
		for (auto &consThread : consThreads)
		{
				consThread.join();
				consumed += consThread.tokens();
		}
		for (auto &prodThread : prodThreads)
		{
				prodThread.join();
				produced += prodThread.tokens();
		}

		// Output
		std::cout << "Producer: " << produced << " tokens" << std::endl;
		std::cout << "Consumer: " << consumed << " tokens" << std::endl;

		// Return
		return 0;
}
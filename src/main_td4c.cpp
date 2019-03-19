#include <functional>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

#include "Semaphore.h"

void consTask(Semaphore &semaphore, unsigned int &n) {
	bool success(true);
	while (success) {
		success = semaphore.take(1000); // 1 second timeout
		if (success) {
			++n;
		}
	}
}

void prodTask(Semaphore &semaphore, unsigned int nTokens) {
	for (unsigned int k = 0; k < nTokens; ++k) {
		semaphore.give();
	}
}

int main(int argc, char **argv) {
	if (argc < 3) {
		std::cerr << "Usage: " << argv[0] << " <nCons> <nProd>\n";
		return 1;
	}
	unsigned int nCons = std::stoul(argv[1]);
	unsigned int nProd = std::stoul(argv[2]);

	unsigned int nTokens(10);

	Semaphore semaphore();

	// Create the threads
	std::vector<std::thread> consThreads{};
	std::vector<unsigned int> nTaken(nCons, 0);
	std::vector<std::thread> prodThreads{};
	for (unsigned int k = 0; k < nCons; ++k) {
		consThreads.push_back(
				std::thread(consTask, std::ref(semaphore), std::ref(nTaken.at(k))));
	}
	for (unsigned int k = 0; k < nProd; ++k) {
		prodThreads.push_back(std::thread(prodTask, std::ref(semaphore), nTokens));
	}

	// Join the threads
	for (auto &thread : consThreads) {
		thread.join();
	}
	for (auto &thread : prodThreads) {
		thread.join();
	}

	// Output
	std::cout << "Producer: " << nProd * nTokens << " tokens\n";
	std::cout << "Consumer: " << std::accumulate(nTaken.begin(), nTaken.end(), 0)
						<< " tokens\n";

	// Return
	return 0;
}
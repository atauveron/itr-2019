#include <array>
#include <functional>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

#include "Fifo.h"
#include "Mutex.h"

int main(int argc, char **argv) {
	if (argc < 3) {
		std::cerr << "Usage: " << argv[0] << " <nCons> <nProd>\n";
		return 1;
	}
	unsigned int nCons = std::stoul(argv[1]);
	unsigned int nProd = std::stoul(argv[2]);

	// Generate integers between 0 and n-1 in each thread.
	constexpr unsigned int n(25);
	Fifo<int> fifo;

	// Create the threads
	std::vector<std::thread> consThreads;
	std::vector<std::thread> prodThreads;
	// Data
	struct Data {
		Mutex mtx;
		std::array<unsigned int, n> nTaken{};
	} data;

	for (unsigned int k = 0; k < nCons; ++k) {
		consThreads.push_back(std::thread(
				[](Fifo<int> &fifo, Data &data) {
					bool active(true);
					while (active) {
						try {
							int tmp = fifo.pop(1000); // 1 second timeout
							Mutex::Lock lck(data.mtx);
							data.nTaken.at(tmp) += 1;
						} catch (const Fifo<int>::EmptyException &e) {
							active = false;
						}
					}
				},
				std::ref(fifo), std::ref(data)));
	}
	for (unsigned int k = 0; k < nProd; ++k) {
		prodThreads.push_back(std::thread(
				[n](Fifo<int> &fifo) {
					for (unsigned int k = 0; k < n; ++k) {
						fifo.push(k);
					}
				},
				std::ref(fifo)));
	}

	// Join the threads
	for (auto &thread : consThreads) {
		thread.join();
	}
	for (auto &thread : prodThreads) {
		thread.join();
	}

	// Check correct execution
	bool correct(true);
	for (auto &it : data.nTaken) {
		if (it != nProd) {
			correct = false;
			break;
		}
	}
	// Output
	std::cout << "Correct execution: " << correct << "\n";

	// Return
	return 0;
}
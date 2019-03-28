#include <functional>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

#include "Semaphore.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <nCons> <nProd>\n";
        return 1;
    }
    unsigned int nCons = std::stoul(argv[1]);
    unsigned int nProd = std::stoul(argv[2]);

    constexpr unsigned int nTokens(10);

    Semaphore semaphore;

    // Create the threads
    std::vector<std::thread> consThreads;
    std::vector<unsigned int> nTaken(nCons, 0);
    std::vector<std::thread> prodThreads;

    for (unsigned int k = 0; k < nCons; ++k) {
        consThreads.push_back(std::thread(
            [](Semaphore &semaphore, unsigned int &n) {
                while (semaphore.take(1000)) { // 1 second timeout
                    ++n;
                }
            },
            std::ref(semaphore), std::ref(nTaken.at(k))));
    }
    for (unsigned int k = 0; k < nProd; ++k) {
        prodThreads.push_back(std::thread(
            [nTokens](Semaphore &semaphore) {
                for (unsigned int k = 0; k < nTokens; ++k) {
                    semaphore.give();
                }
            },
            std::ref(semaphore)));
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
    std::cout << "Consumer: "
              << std::accumulate(nTaken.begin(), nTaken.end(), 0)
              << " tokens\n";

    // Return
    return 0;
}
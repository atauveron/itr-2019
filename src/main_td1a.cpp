/**
 * @file main_td1a.cpp
 * @brief Main file for tutorial question 1a
 */
#include <csignal>
#include <ctime>
#include <iostream>

/**
 * @brief A handler function for the timer
 * This function decrements the value of the integer counter passed via @p si.
 *
 * @param sig
 * @param si
 */
void handler(int, siginfo_t *si, void *) {
    int *counter = reinterpret_cast<int *>(si->si_value.sival_ptr);
    --(*counter);
    // DEBUG
    std::cout << "Handler called with value " << *counter << '\n';
    return;
}

int main() {
    int counter(15);

    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, nullptr);

    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = &counter;

    timer_t tid;
    timer_create(CLOCK_REALTIME, &sev, &tid);
    itimerspec its;
    its.it_value = {0, 500000000};
    its.it_interval = {0, 500000000};
    timer_settime(tid, 0, &its, nullptr);
    while (counter > 0) {
	// Nothing to do
    }
    its.it_value = {0, 0};
    timer_settime(tid, 0, &its, nullptr);
    // Wait for the signal
    timer_delete(tid);

    // Return
    return 0;
}

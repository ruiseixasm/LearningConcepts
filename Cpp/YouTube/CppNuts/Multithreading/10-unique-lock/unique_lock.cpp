// TOPIC: unique_lock in C++ (std::unique_lock<mutex> lock(m1))

// NOTES:
// 1. The class unique_lock is a mutex ownership wrapper.
// 2. It Allows:
//     a. can have different locking strategies
//     b. time-constrained attempts at locking (try_lock_for, try_lock_until)
//     c. recursive locking
//     d. transfer of lock ownership (move not copy)
//     e. condition variables. (see this in coming videos)

// Locking Strategies
// TYPE                 EFFECTS
// 1. defer_lock        do not acquire ownership of the mutex.
// 2. try_to_lock       try to acquire ownership of the mutex without blocking.
// 3. adpot_lock        assume the calling thread already has ownership of the mutex.

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

std::mutex m1;
int buffer = 0;

// EXAMPLE 1

void task(const char* threadName, int loopFor) {
    std::unique_lock<mutex> lock(m1);   // Automatically calls lock on mutex m1
    for (int i = 0; i < loopFor; ++i) {
        buffer++;
        cout << threadName << buffer << endl;
    }
}

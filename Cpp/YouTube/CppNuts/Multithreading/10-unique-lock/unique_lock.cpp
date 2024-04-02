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
void task_1(const char* threadName, int loopFor) {
    std::unique_lock<mutex> lock(m1);   // Automatically calls lock on mutex m1
    for (int i = 0; i < loopFor; ++i)
        cout << threadName << ++buffer << endl;
}

// EXAMPLE 2
void task_2(const char* threadName, int loopFor) {
    std::unique_lock<mutex> lock(m1, std::defer_lock);   // Doesn't call lock on mutex m1
    lock.lock();    // defer_lock requires the explicit lock afterwards
    for (int i = 0; i < loopFor; ++i)
        cout << threadName << ++buffer << endl;
    // lock.unlock(); is not necessary as it will be called by the unique_lock destructor
}

int main() {
    thread t1a(task_1, "T1A ", 10);
    thread t1b(task_1, "T1B ", 10);
    thread t2a(task_2, "T2A ", 10);
    thread t2b(task_2, "T2B ", 10);
    t1a.join();
    t1b.join();
    t2a.join();
    t2b.join();

    return 0;
}
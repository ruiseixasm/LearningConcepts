// TOPiC: lock_guard in C++ (std::lock_guard<mutex> lock(m1))

// NOTES:
// 0. It is very light weight wrapper for owning mutex on scoped basis.
// 1. It aquires mutex lock the moment you create the object of lock_guard.
// 2. It automatically removes the lock while goes out of scope.
// 3. You can not explicitly unlock the lock_guard.
// 4. You can not copy lock_guard.

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

std::mutex m1;
int buffer = 0;

void task_mutex(const char* threadName, int loopFor) {
    m1.lock();
    for (int i = 0; i < loopFor; ++i) {
        buffer++;
        cout << threadName << buffer << endl;
    }
    m1.unlock();
}

void task_lock_guard(const char* threadName, int loopFor) {
    std::lock_guard<mutex> lock(m1);
    for (int i = 0; i < loopFor; ++i) {
        buffer++;
        cout << threadName << buffer << endl;
    }
}

int main() {
    thread tm1(task_mutex, "TM0 ", 10);
    thread tm2(task_mutex, "TM1 ", 10);
    thread tlg1(task_lock_guard, "TLG0 ", 10);
    thread tlg2(task_lock_guard, "TLG1 ", 10);
    tm1.join();
    tm2.join();
    tlg1.join();
    tlg2.join();

    return 0;
}
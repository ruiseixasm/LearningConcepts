// TOPIC: Condition Variable In C++ Threading

// IMPORTANT POINT: CV are used for two purposes
// A. Notify other threads
// B. Waiting for some conditions

// 1. Condition Variable allows running threads to wait on some conditions
//    and once those conditions are met the waiting thread is notified using:
//      a. notify_one();
//      b. notify_all();
// 2. You need mutex to use condition variable.
// 3. If some thread wants to wait on some condition then it has to do these things:
//      a. Acquire the mutex lock using std::unique_lock<std::mutex> lock(m);.
//      b. Execute wait, wait_for, or wait_until. The wait operations atomacally release the mutex
//         and suspend the execution of the thread.
//      c. When the condition variable is notified, the thread is awakened, and the mutex is
//         atomacally reacquired.
//         The thread should then check the condition and resume waiting if the wake up was spurious.

// NOTE:
// 1. Condition variables are used to synchronize two or more threads.
// 2. Best use case of condition variables is Producer/Consumer problem.

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

std::condition_variable cv;
std::mutex m;
long balance = 0;


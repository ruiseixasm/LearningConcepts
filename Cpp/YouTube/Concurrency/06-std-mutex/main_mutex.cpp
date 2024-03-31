#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

// Compile with: g++ -std=c++17 main.cpp -o main.out [-lpthread]

std::mutex gLock; // Mutex = Binary Semaphore
static int shared_value = 0; // There is the problem of reading old values and total not being correct

void shared_value_increment() {
    gLock.lock();
        // atomic section of code
        int value = shared_value;
        shared_value = value + 1;
    gLock.unlock();
}

int main() {

    std::vector<std::thread> threads;
    for (size_t i = 0; i < 1000; i++) {
        threads.push_back(std::thread(shared_value_increment));
    }

    for (size_t i = 0; i < 1000; i++) { // avoids the termination of the main before the terminatoin of the thread
        threads[i].join();
    }

    std::cout << "Shared value: " << shared_value << std::endl;
    return 0;
}
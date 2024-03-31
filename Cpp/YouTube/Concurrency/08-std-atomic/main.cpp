#include <iostream>
#include <thread>
#include <vector>
#include <atomic> // instead of <mutex>

// Compile with: g++ -std=c++17 main.cpp -o main.out [-lpthread]

static std::atomic<int> shared_value = 0; // Defined as atomic variable so protected to deadlock!

void shared_value_increment() {
    // atomic section of code
    shared_value++; // use only ++ or += and NOT +
    // Don't use "shared_value = shared_value + 1" beacause + operator isn't overloaded by atomic!!!
}

int main() {

    std::vector<std::thread> threads;
    for (size_t i = 0; i < 100; i++) {
        threads.push_back(std::thread(shared_value_increment));
    }

    for (size_t i = 0; i < 100; i++) { // avoids the termination of the main before the terminatoin of the thread
        threads[i].join();
    }

    std::cout << "Shared value: " << shared_value << std::endl;
    return 0;
}
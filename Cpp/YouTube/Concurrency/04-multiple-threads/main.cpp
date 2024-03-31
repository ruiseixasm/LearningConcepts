#include <iostream>
#include <thread>
#include <vector>

// Compile with: g++ -std=c++17 main.cpp -o main.out [-lpthread]


int main() {

    auto lambda = [](int X) {
        std::cout << "Hello from thread!" << std::this_thread::get_id() << std::endl;
        std::cout << "Argument passed in: " << X << std::endl;
    };

    std::vector<std::thread> threads;
    for (size_t i = 0; i < 10; i++) {
        threads.push_back(std::thread(lambda, 100));
    }

    for (size_t i = 0; i < 10; i++) { // avoids the termination of the main before the terminatoin of the thread
        threads[i].join();
    }

    std::cout << "Hello from my main thread" << std::endl;
    return 0;
}
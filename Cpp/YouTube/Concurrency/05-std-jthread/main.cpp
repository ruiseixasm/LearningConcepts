#include <iostream>
#include <thread>
#include <vector>

// Compile with: g++ -std=c++20 main.cpp -o main.out [-lpthread]


int main() {

    auto lambda = [](int X) {
        std::cout << "Hello from thread!" << std::this_thread::get_id() << std::endl;
        std::cout << "Argument passed in: " << X << std::endl;
    };

    std::vector<std::jthread> j_threads;
    for (size_t i = 0; i < 10; i++) {
        j_threads.push_back(std::jthread(lambda, 100));
    }

    std::cout << "Hello from my main thread" << std::endl;
    return 0;
}
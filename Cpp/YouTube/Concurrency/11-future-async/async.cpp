// @file async.cpp
#include <iostream>
#include <future>

int square(int x) {
    return x*x;
}

int main() {
    std::future<int> asyncFunction = std::async(&square, 12);
    // Some other work to do simultaneously
    for (size_t i = 0; i < 10; i++) {
        std::cout << square(i) << std::endl;
    }
    // Returns the result of our future
    // Blocked as long as result isn't ready or future done
    int result = asyncFunction.get();
    std::cout << "result is: " << result << std::endl;

    return 0;
}
#include <iostream>
#include <thread>

void test(int X) {
    std::cout << "Hello from thread!" << std::endl;
    std::cout << "Argument passed in: " << X << std::endl;
}

int main() {
    std::thread my_thread(&test, 100);
    my_thread.join(); // avoids the termination of the main before the terminatoin of the thread

    std::cout << "Hello from my main thread" << std::endl;
    return 0;
}
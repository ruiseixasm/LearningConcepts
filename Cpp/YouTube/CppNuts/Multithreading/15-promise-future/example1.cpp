#include <iostream>
#include <thread>
#include <future>
using namespace std;

void doWork(std::promise<int>&& promiseObj) {
    promiseObj.set_value(42);
}

int main() {

    std::promise<int> pObj;

    std::future<int> fObj = pObj.get_future();
    std::thread thread_A(doWork, std::move(pObj));

    std::cout << fObj.get() << std::endl;
    std::cout << "Completed!!" << std::endl;
    thread_A.join();    // Always need to join the thread

    return 0;
}
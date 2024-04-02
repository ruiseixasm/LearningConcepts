#include <iostream>
#include <sstream>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

class ThreadPool {
public:
    ThreadPool(size_t numThreads) : stop(false) {
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back([this] {
                for (;;) {
                    std::unique_lock<std::mutex> lock(queueMutex);
                    condition.wait(lock, [this] { return stop || !tasks.empty(); });
                    if (stop && tasks.empty())
                        return;
                    auto task = std::move(tasks.front());   // 1. Extract task from tasks list.
                    tasks.pop();    // 2. Remove tasks from list as going to execute it.
                    lock.unlock();  // 3. Unlock mutex, so another thread can accept another task.
                    task();         // 4. Run the extracted task.
                }
            });
        }
    }

    template<class F>
    void enqueue(F&& task) {
        std::unique_lock<std::mutex> lock(queueMutex);
        tasks.emplace(std::forward<F>(task));
        lock.unlock();
        condition.notify_one();
    }

    ~ThreadPool() {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
        lock.unlock();
        condition.notify_all();
        for (std::thread& worker : workers) {
            std::cout << "Worker joined: " << worker.get_id() << std::endl;
            worker.join();
        }
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;    // tasks must have a function signature of void()

    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;
};

std::string get_thread_id() {
    auto myid = std::this_thread::get_id();
    std::stringstream ss;
    ss << myid;
    std::string mystr = ss.str();
    return mystr;
}

int main() {

    ThreadPool pool(4); // Create a pool with N number of worker threads

    std::cout << "Thread Pool Created\n";
    std::cout << "Equeue (Assign) some tasks\n";

    // Job pushing task
    for (int i = 0; i < 16; ++i) {
        pool.enqueue([i] {  // task signature: void()
            std::this_thread::sleep_for(std::chrono::seconds(1));   // Simulate some work
            printf("Task %d %s executed by thread\n", i, get_thread_id().c_str());
        });
    }

    // Main thread continues doing other things
    // while the tasks are executed in the background

    return 0;
}
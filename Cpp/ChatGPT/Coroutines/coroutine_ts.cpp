#include <iostream>
#include <experimental/coroutine>

// Define a generator coroutine that yields integers from 0 to limit
class Generator {
public:
    // Constructor
    Generator(int limit) : limit(limit) {}

    // Coroutine promise type
    struct promise_type {
        int current_value;

        auto initial_suspend() noexcept { return std::experimental::suspend_always{}; }
        auto final_suspend() noexcept { return std::experimental::suspend_always{}; }

        Generator get_return_object() noexcept {
            return Generator{std::experimental::coroutine_handle<promise_type>::from_promise(*this)};
        }

        void return_void() noexcept {}

        auto yield_value(int value) noexcept {
            current_value = value;
            return std::experimental::suspend_always{};
        }

        // Coroutine support requires special deallocation function
        static void operator delete(void* ptr) noexcept {
            ::operator delete(ptr);
        }
    };

    // Iterator for the generator
    struct Iterator {
        std::experimental::coroutine_handle<promise_type> coro;

        void operator++() { coro.resume(); }

        int operator*() { return coro.promise().current_value; }

        bool operator==(std::nullptr_t) const { return !coro || coro.done(); }
        bool operator!=(std::nullptr_t) const { return !(*this == nullptr); }
    };

    Iterator begin() {
        if (coro) coro.resume();
        return Iterator{coro};
    }

    std::nullptr_t end() { return nullptr; }

private:
    int limit;
    std::experimental::coroutine_handle<promise_type> coro;
};

// Coroutine function that yields integers from 0 to limit
Generator count_to(int limit) {
    for (int i = 0; i <= limit; ++i) {
        co_yield i;
    }
}

int main() {
    // Iterate over the coroutine
    for (int i : count_to(5)) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}

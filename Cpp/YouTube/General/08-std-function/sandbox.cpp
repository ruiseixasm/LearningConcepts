#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>   // wrapper of storage of "callable objects"

using namespace std;

// Function
void foo(int x) {
    cout << x << endl;
}

// Functor
struct SF {
    void operator()(int x) {
        cout << x << endl;
    }
};

void foo_foo(function<void(int)> func) {
    func(25);
}

int main() {
    function<void(int)> f = foo;    // void(int) is the function signature
    f(5);

    function<void(int)> lf = [](int x) {cout << x << endl;};
    lf(10);

    auto alf = [](int x) {cout << x << endl;};
    alf(15);

    SF sf;
    function<void(int)> fun = sf;
    fun(20);

    foo_foo(alf);
    foo_foo(foo);
    foo_foo(sf);

    vector<function<void(int)>> vf;

    vf.push_back(f);
    vf.push_back(lf);
    vf.push_back(fun);

    for (auto& vfunction : vf) {
        vfunction(30);
    }

    // Calling a std::function is slower than call it nativelly, so, don't over use it

    return 0;
}
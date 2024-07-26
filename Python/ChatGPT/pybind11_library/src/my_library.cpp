#include "my_library.hpp"

int add(int a, int b) {
    return a + b;
}

PYBIND11_MODULE(my_library, m) {
    m.def("add", &add, "A function which adds two numbers");
}

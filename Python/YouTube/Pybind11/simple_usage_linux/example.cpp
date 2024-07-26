// Command line: g++ -shared -fPIC example.cpp $(pipx run pybind11 --includes) \
                     -o example$(python3-config --extension-suffix)

/*
    How to install pipx:
        python3 -m pip install --user pipx
        python3 -m pipx ensurepath
*/

#include <pybind11/pybind11.h>

int add(int i, int j) {
    return i + j;
}

PYBIND11_MODULE(example, m) {
    m.def("add", &add);
}

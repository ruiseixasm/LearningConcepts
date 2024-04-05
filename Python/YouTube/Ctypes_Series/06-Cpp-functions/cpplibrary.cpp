#include <iostream>
#include <string>

// C++ changes the names behind the scenes (name mangling)
//      _func_v, _func_i, _func_s, _func_si
// C does NOT support name mangling (function overloading)
//      _func_ only

void func() {
    std::cout << "Function with NO parameters" << std::endl;
}

void func(int n) {
    std::cout << "Function with an int parameter" << std::endl;
}

void func(std::string a) {
    std::cout << "Function with a string parameter" << std::endl;
}

void func(std::string a, int n) {
    std::cout << "Function with a string parameter" << std::endl;
}

extern "C" {    // Tells our compiler it will be used as C language without name mangling

    // Without overloading
    void func_c() {
        func();
    }

    // void func() {
    //     std::cout << "Function with NO parameters" << std::endl;
    // }

    // void func(int n) {
    //     std::cout << "Function with an int parameter" << std::endl;
    // }

    // void func(std::string a) {
    //     std::cout << "Function with a string parameter" << std::endl;
    // }

    // void func(std::string a, int n) {
    //     std::cout << "Function with a string parameter" << std::endl;
    // }

}


// Generate the .so file with this command
// g++ cpplibrary.cpp -shared -o cpplibrary.so -fPIC

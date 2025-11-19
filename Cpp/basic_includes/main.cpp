#include "include_lib.h"
#include <iostream>

int main() {
    std::cout << "Hello World!" << std::endl;
    IncludeLib *lib_include = new IncludeLib();
    lib_include->PrintText();
    return 0;
}
#include <iostream>
#include "lib/lowlevelmath.h"

int main() {
    std::cout << "Hello World!" << std::endl;

    // Using the LowLevelAdd function from the shared library
    int result = LowLevelAdd(3, 4);
    std::cout << "Result of adding 3 and 4: " << result << std::endl;

    return 0;
}


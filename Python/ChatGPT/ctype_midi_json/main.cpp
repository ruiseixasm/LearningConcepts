#include <iostream>
#include "my_library.hpp"

int main() {
    int result = add_original(3, 4);
    std::cout << "3 + 4 = " << result << std::endl;
    return 0;
}

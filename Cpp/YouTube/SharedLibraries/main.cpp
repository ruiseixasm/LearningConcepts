// A simple example of linking against a static library
// By: Nick from CoffeeBeforeArch

#include <iostream>
#include "add.h"
#include "multiply.h"

int main() {
    // Use our add function
    auto sum = add(10, 20);
    std::cout << "Sum: " << sum << std::endl;

    // Use our multiply function
    auto product = multiply(10, 20);
    std::cout << "product: " << product << std::endl;

    return 0;
}
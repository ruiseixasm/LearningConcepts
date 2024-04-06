#include <iostream>

// A deprecated function
[[deprecated("Use newFunction() instead")]]
void deprecatedFunction() {
    std::cout << "This function is deprecated\n";
}

// A function that should not have its return value ignored
[[nodiscard]]
int calculateValue(int x, int y) {
    return x * y;
}

// A function that never returns
[[noreturn]]
void neverReturn() {
    std::cout << "This function never returns\n";
    std::exit(1); // Exit the program
}

int main() {
    // Calling the deprecated function
    deprecatedFunction();

    // Ignoring the return value of calculateValue()
    calculateValue(5, 10); // Compiler may issue a warning here

    // Calling a function that never returns
    neverReturn();

    // Compiler may issue a warning about falling through this switch statement
    int option = 2;
    switch (option) {
        case 1:
            std::cout << "Option 1\n";
            [[fallthrough]];
        case 2:
            std::cout << "Option 2\n";
            break;
        default:
            std::cout << "Default option\n";
    }

    return 0;
}


// In C++, attributes are used to provide additional information or constraints to various entities
//     such as functions, variables, or classes. Here are some examples of attributes other than extern "C":

//     [[nodiscard]]: Indicates that the return value of a function should not be ignored.
//     [[deprecated]]: Marks a function, variable, or type as deprecated, indicating that
//                     it should be avoided in favor of an alternative.
//     [[maybe_unused]]: Suppresses compiler warnings about unused variables or entities.
//     [[noreturn]]: Specifies that a function does not return (e.g., due to calling exit()
//                     or throwing an exception).
//     [[fallthrough]]: Suppresses compiler warnings about falling through a case label in a switch statement.

// These are just a few examples of attributes in C++. There are many others, and new ones may be introduced
//     in future language standards. Each attribute serves a specific purpose, providing additional
//     information to the compiler or affecting its behavior in some way.
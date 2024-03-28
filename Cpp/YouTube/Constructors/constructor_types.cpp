#include <iostream>

/* Types of Constructor
 *  1. Default constructor
 *  2. Parameterized constructor
 *  3. Copy constructor
 */

class Example {
private:
    int data;

public:
    // Default constructor
    Example() : data(0) {
        std::cout << "Default constructor called. Data initialized to 0." << std::endl;
    }

    // Parameterized constructor
    Example(int value) : data(value) {
        std::cout << "Parameterized constructor called. Data initialized to " << value << "." << std::endl;
    }

    // Copy constructor
    Example(const Example& other) : data(other.data) {
        std::cout << "Copy constructor called. Data copied from another object." << std::endl;
    }

    // Member function to display data
    void displayData() {
        std::cout << "Data: " << data << std::endl;
    }
};

int main() {

    // Using the default constructor
    Example obj1;

    // Using the parameterized constructor
    Example obj2(42);

    // Using the copy constructor
    Example obj3(obj2);

    // Displaying data
    obj1.displayData();
    obj2.displayData();
    obj3.displayData();

    return 0;
}
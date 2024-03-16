#include <iostream>

// Run command line: g++ -std=c++17 CopyMoveConstructors.cpp -o CopyMoveConstructors.out

class MyClass {
public:
    int* data;

    // Constructor
    MyClass(int value) {
        data = new int(value);
        std::cout << "Constructor called, value: " << *data << std::endl;
    }

    // Copy constructor
    MyClass(const MyClass& other) {
        std::cout << "Copy constructor called" << std::endl;
        data = new int(*other.data); // Perform deep copy
    }

    // Move constructor
    MyClass(MyClass&& other) noexcept {
        std::cout << "Move constructor called" << std::endl;
        data = other.data;    // Transfer ownership of data pointer
        other.data = nullptr; // Invalidate data pointer of the source object
    }

    // Destructor
    ~MyClass() {
        if (data != nullptr) {
            std::cout << "Destructor called, value: " << *data << std::endl;
            delete data;
        }
    }
};

int main() {
    // Create an object of MyClass
    MyClass obj1(5);

    // Use copy constructor to create obj2 as a copy of obj1
    MyClass obj2 = obj1;

    // Use move constructor to create obj3 by moving resources from obj1
    MyClass obj3 = std::move(obj1);

    // Output the data members of obj2 and obj3
    std::cout << "obj2.data: " << obj2.data << std::endl;
    std::cout << "obj3.data: " << obj3.data << std::endl;

    return 0;
}

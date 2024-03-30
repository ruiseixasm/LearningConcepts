#include <iostream>
#include <memory>

class MyClass {
private:
    int value;
public:
    MyClass(int val) : value(val) {}
    void printValue() const {
        std::cout << "Value: " << value << std::endl;
    }
};

// Function that takes std::unique_ptr as parameter
void processUniquePtr(std::unique_ptr<MyClass> ptr) {
    if (ptr) {
        std::cout << "Processing unique_ptr with value: ";
        ptr->printValue();
    } else {
        std::cout << "Null unique_ptr passed to function." << std::endl;
    }
}

// Function that returns std::unique_ptr
std::unique_ptr<MyClass> createUniquePtr(int val) {
    return std::make_unique<MyClass>(val);
}

// Function that takes std::unique_ptr as parameter and returns it as a reference
std::unique_ptr<MyClass>& passUniquePtr(std::unique_ptr<MyClass>& ptr) {
    return ptr;
}

int main() {
    // Creating std::unique_ptr for a primitive type
    std::unique_ptr<int> intPtr = std::make_unique<int>(42);

    // Accessing the managed object
    std::cout << "Value stored in intPtr: " << *intPtr << std::endl;

    // Creating std::unique_ptr for a class object
    std::unique_ptr<MyClass> classPtr = std::make_unique<MyClass>(10);

    // Accessing the managed object's member function
    classPtr->printValue();

    // Resetting std::unique_ptr to manage a new object
    classPtr.reset(new MyClass(20));
    classPtr->printValue();

    // Releasing ownership from std::unique_ptr
    MyClass* rawPtr = classPtr.release();
    if (rawPtr) {
        std::cout << "Value released from classPtr: ";
        rawPtr->printValue();
        delete rawPtr; // Remember to delete the raw pointer to avoid memory leaks
    }

    // Pass std::unique_ptr to a function
    processUniquePtr(std::move(classPtr)); // std::move is used to transfer ownership
    // classPtr is now nullptr after being moved

    // Function returning std::unique_ptr
    std::unique_ptr<MyClass> newPtr = createUniquePtr(30);
    newPtr->printValue();

    // Creating std::unique_ptr for a class object
    newPtr = std::make_unique<MyClass>(10); // NO MEMORY LEAK!

    // Pass std::unique_ptr to the function and receive it back
    std::unique_ptr<MyClass>& returnedPtr = passUniquePtr(newPtr);

    // Accessing the managed object's member function
    returnedPtr->printValue();

    return 0;
}

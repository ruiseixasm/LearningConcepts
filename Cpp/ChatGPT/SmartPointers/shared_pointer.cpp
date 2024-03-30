#include <iostream>
#include <memory>

// Sample class
class MyClass {
private:
    int data;
public:
    MyClass(int data) : data(data) {}
    void printData() const {
        std::cout << "Data: " << data << std::endl;
    }
};

// Function taking shared_ptr as parameter
void funcWithSharedPtr(std::shared_ptr<int> ptr) {
    std::cout << "Inside funcWithSharedPtr: " << *ptr << std::endl;
}

// Function returning shared_ptr
std::shared_ptr<MyClass> createSharedPtr() {
    return std::make_shared<MyClass>(100);
}

// Function taking and returning shared_ptr by reference
void passSharedPtr(std::shared_ptr<int>& ptr) {
    std::cout << "Inside passSharedPtr: " << *ptr << std::endl;
    // Modify the value
    *ptr = 200;
}

int main() {
    // Shared pointer to a primitive int
    std::shared_ptr<int> intPtr = std::make_shared<int>(42);

    // Shared pointer to a class object
    std::shared_ptr<MyClass> classPtr = std::make_shared<MyClass>(50);

    // Accessing and modifying the data
    *intPtr = 55;
    classPtr->printData();

    // Passing shared_ptr as parameter
    funcWithSharedPtr(intPtr);

    // Returning shared_ptr from a function
    std::shared_ptr<MyClass> ptrFromFunc = createSharedPtr();
    ptrFromFunc->printData();

    // Passing and returning shared_ptr by reference
    passSharedPtr(intPtr);
    std::cout << "After passSharedPtr: " << *intPtr << std::endl;

    // Creating a shared pointer
    std::shared_ptr<int> ptr1 = std::make_shared<int>(42);

    // Creating another shared pointer pointing to the same object
    std::shared_ptr<int> ptr2 = ptr1;

    // Getting the total count of shared pointers
    std::cout << "Total count of shared pointers: " << ptr1.use_count() << std::endl;

    return 0;
}

#include <iostream>
#include <memory>

class MyClass {
private:
    int data;
public:
    MyClass(int value) : data(value) {}

    void printData() const {
        std::cout << "Data: " << data << std::endl;
    }
};

// Function taking weak_ptr as parameter
void processWeakPtr(std::weak_ptr<MyClass> weakPtr) {
    if (auto sharedPtr = weakPtr.lock()) {
        sharedPtr->printData();
    } else {
        std::cout << "Weak pointer is expired." << std::endl;
    }
}

// Function returning weak_ptr
std::weak_ptr<MyClass> createWeakPtr(int value) {
    std::shared_ptr<MyClass> sharedPtr = std::make_shared<MyClass>(value);
    return sharedPtr;
}

// Function taking and returning weak_ptr as references
void passWeakPtr(std::weak_ptr<MyClass>& weakPtr) {
    processWeakPtr(weakPtr);
}

int main() {
    // Creating a shared_ptr and obtaining a weak_ptr from it
    std::shared_ptr<MyClass> sharedPtr = std::make_shared<MyClass>(42);
    std::weak_ptr<MyClass> weakPtr = sharedPtr;

    // Using weak_ptr
    processWeakPtr(weakPtr);

    // Creating a weak_ptr using a function
    std::weak_ptr<MyClass> weakPtrFromFunction = createWeakPtr(100);

    // Using weak_ptr returned from function
    processWeakPtr(weakPtrFromFunction);

    // Passing and using weak_ptr as parameter and return type
    passWeakPtr(weakPtr);

    return 0;
}

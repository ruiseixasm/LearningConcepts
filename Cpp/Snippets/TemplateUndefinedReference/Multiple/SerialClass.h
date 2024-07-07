#pragma once
#include <iostream>

class SerialClass {
private:
    unsigned long int boud_rate;
public:
    // Non-template method - declaration only, definition in the .cpp file
    void begin(unsigned long int boud);

    // Template method - must be defined in the header
    template <typename T>
    void print(const T& data);

    // Template method - must be defined in the header
    template <typename T>
    void println(const T& data);

    // Non-template method - declaration only, definition in the .cpp file
    // Overloads for print with no arguments to just start a new line
    void println();
};

// Template method definition in the header file
template <typename T>
void SerialClass::print(const T& data) {
    std::cout << "(" << boud_rate << ") : " << data;
}

// Template method definition in the header file
template <typename T>
void SerialClass::println(const T& data) {
    std::cout << "(" << boud_rate << ") : " << data << std::endl;
}

// Instantiate a global Serial object similar to Arduino
extern SerialClass Serial;

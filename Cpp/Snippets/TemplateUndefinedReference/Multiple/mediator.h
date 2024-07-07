#pragma once

#include <iostream>

class SerialClass {
private:
    unsigned long int boud_rate;
public:
    template <typename T>
    void print(const T& data);

    template <typename T>
    void println(const T& data);

};

template <typename T>
void SerialClass::print(const T& data) {
    std::cout << "(" << boud_rate << ") : " << data;
}

template <typename T>
void SerialClass::println(const T& data) {
    std::cout << "(" << boud_rate << ") : " << data << std::endl;
}

// Instantiate a global Serial object similar to Arduino
//extern SerialClass Serial;



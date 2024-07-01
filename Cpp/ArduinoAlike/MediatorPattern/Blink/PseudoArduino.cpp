#include "PseudoArduino.h"

#ifndef  ARDUINO


template <typename T>
void SerialClass::print(const T& data) {
    std::cout << data;
}

template <typename T>
void SerialClass::println(const T& data) {
    std::cout << data << std::endl;
}

void SerialClass::println() {
    std::cout << std::endl;
}

// Instantiate a global Serial object similar to Arduino
static SerialClass Serial;

#endif

#ifndef  ARDUINO

#include "PseudoArduino.h"

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


// Function to mimic Arduino's delay function
void delay(unsigned long milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}


#endif

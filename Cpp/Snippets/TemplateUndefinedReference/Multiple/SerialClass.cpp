#include "SerialClass.h"

// Non-template method definition in the source file
void SerialClass::begin(unsigned long int boud) {
    boud_rate = boud;
}

// Non-template method definition in the source file
void SerialClass::println() {
    std::cout << "(" << boud_rate << ") : " << std::endl;
}

// Instantiate a global Serial object similar to Arduino
SerialClass Serial;


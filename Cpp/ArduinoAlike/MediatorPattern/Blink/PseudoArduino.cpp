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
SerialClass Serial;


// Function to mimic Arduino's delay function
void delay(unsigned long milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}


std::string Microcontroller::modeToString(PinMode mode) {
    switch (mode) {
        case INPUT: return "INPUT";
        case OUTPUT: return "OUTPUT";
        case INPUT_PULLUP: return "INPUT_PULLUP";
        default: return "UNKNOWN";
    }
}

void Microcontroller::pinMode(int pin, PinMode mode) {
    pinModes[pin] = mode;
    std::string modeStr = modeToString(mode);
    std::cout << "Pin " << pin << " set to " << modeStr << " mode." << std::endl;
}

void Microcontroller::digitalWrite(int pin, int value) {
    if (pinModes.find(pin) == pinModes.end()) {
        std::cerr << "Error: Pin " << pin << " not configured. Use pinMode() first." << std::endl;
        return;
    }
    pinStates[pin] = (value == HIGH) ? HIGH_STATE : LOW_STATE;
    std::string stateStr = (value == HIGH) ? "HIGH" : "LOW";
    std::cout << "Pin " << pin << " set to " << stateStr << "." << std::endl;
}

void Microcontroller::printPinStates() {
    for (const auto &entry : pinStates) {
        std::string stateStr = (entry.second == HIGH_STATE) ? "HIGH" : "LOW";
        std::cout << "Pin " << entry.first << " is " << stateStr << "." << std::endl;
    }
}

// Define the global microcontroller instance
Microcontroller MCU;

// Function to mimic Arduino's pinMode()
void pinMode(int pin, PinMode mode) {
    MCU.pinMode(pin, mode);
}

// Function to mimic Arduino's digitalWrite()
void digitalWrite(int pin, int value) {
    MCU.digitalWrite(pin, value);
}







#endif

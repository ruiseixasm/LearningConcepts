#ifndef  ARDUINO

#include "PseudoArduino.h"


void SerialClass::begin(unsigned long int boud) {
    boud_rate = boud;
}

void SerialClass::println() {
    std::cout << "(" << boud_rate << ") : " << std::endl;
}

// Instantiate a global Serial object similar to Arduino
SerialClass Serial;


// Function to mimic Arduino's delay function
void delay(unsigned long milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}


Microcontroller::Microcontroller(const std::vector<int>& values)
    : readValues(values), currentIndex(0) {

    lastReadTime = std::chrono::steady_clock::now() - std::chrono::seconds(1);
}

Microcontroller::Microcontroller() : currentIndex(0) {
    // Initialize random seed based on current time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate a default array of random values (LOW or HIGH)
    for (int i = 0; i < 10; ++i) {  // Adjust the size of the array as needed
        readValues.push_back(std::rand() % 2);
    }

    lastReadTime = std::chrono::steady_clock::now() - std::chrono::seconds(1);
}

Microcontroller::~Microcontroller() {
    // In the provided Microcontroller class, there is no need for a custom destructor
    //     because the class does not manage any resources that require explicit release.
    // The compiler-generated destructor will be sufficient.
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

int Microcontroller::digitalRead(int pin) {
    auto now = std::chrono::steady_clock::now();
    auto durationSinceLastRead = std::chrono::duration_cast<std::chrono::seconds>(now - lastReadTime);

    if (durationSinceLastRead.count() < 1) {
        return readValues.back();
    } else {
        lastReadTime = now;
        int value = readValues[currentIndex];
        currentIndex = (currentIndex + 1) % readValues.size();
        return value;
    }
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

// Function to mimic Arduino's digitalRead()
int digitalRead(int pin) {
    return MCU.digitalRead(pin);
}






#endif

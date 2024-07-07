#pragma once


#include <iostream>

class SerialClass {
private:
    unsigned long int boud_rate;
public:
    void begin(unsigned long int boud);

    template <typename T>
    void print(const T& data);

    template <typename T>
    void println(const T& data);

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

// Promisses an instantiate a global Serial object similar to Arduino
extern SerialClass Serial;

#include <chrono>
#include <thread>
//#define _GLIBCXX_USE_NANOSLEEP

// Function to mimic Arduino's delay function
void delay(unsigned long milliseconds);


#include <vector>
#include <unordered_map>

// Define constants for HIGH and LOW
#define HIGH 1
#define LOW 0

// Macro definition for LED_BUILTIN
#define LED_BUILTIN 13

// Enum for pin modes
enum PinMode {
    INPUT,
    OUTPUT,
    INPUT_PULLUP
};

// Enum for pin states
enum PinState {
    LOW_STATE,
    HIGH_STATE
};

// Microcontroller simulation class
class Microcontroller {
private:
    std::unordered_map<int, PinMode> pinModes;
    std::unordered_map<int, PinState> pinStates;
    std::string modeToString(PinMode mode);
    std::vector<int> readValues;
    std::chrono::time_point<std::chrono::steady_clock> lastReadTime;
    size_t currentIndex;
public:
    void pinMode(int pin, PinMode mode);
    void digitalWrite(int pin, int value);
    int digitalRead(int pin);
    void printPinStates();
    Microcontroller(const std::vector<int>& values);
    Microcontroller();  // Default constructor
    ~Microcontroller(); // Destructor
};


// Promisses the MCU is defined as global instance in other file
extern Microcontroller MCU;

// Function to mimic Arduino's pinMode()
void pinMode(int pin, PinMode mode);

// Function to mimic Arduino's digitalWrite()
void digitalWrite(int pin, int value);

// Function to mimic Arduino's digitalRead()
int digitalRead(int pin);



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

// Promisses an instantiate a global Serial object similar to Arduino
extern SerialClass Serial;

#include <chrono>
#include <thread>
//#define _GLIBCXX_USE_NANOSLEEP

// Function to mimic Arduino's delay function
void delay(unsigned long milliseconds);


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
public:
    void pinMode(int pin, PinMode mode);
    void digitalWrite(int pin, int value);
    void printPinStates();
};


// Promisses the MCU is defined as global instance in other file
extern Microcontroller MCU;

// Function to mimic Arduino's pinMode()
void pinMode(int pin, PinMode mode);

// Function to mimic Arduino's digitalWrite()
void digitalWrite(int pin, int value);




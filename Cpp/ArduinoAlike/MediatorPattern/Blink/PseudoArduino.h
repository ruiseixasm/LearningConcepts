#pragma once

#include <iostream>
#include <chrono>
#include <thread>

class SerialClass {
public:
    template <typename T>
    void print(const T& data);

    template <typename T>
    void println(const T& data);

    // Overloads for print with no arguments to just start a new line
    void println();
};


// Function to mimic Arduino's delay function
void delay(unsigned long milliseconds);


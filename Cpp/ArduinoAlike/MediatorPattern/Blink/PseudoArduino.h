#pragma once

#ifndef  ARDUINO

#include <iostream>

class SerialClass {
public:
    template <typename T>
    void print(const T& data);

    template <typename T>
    void println(const T& data);

    // Overloads for print with no arguments to just start a new line
    void println();
};

#endif

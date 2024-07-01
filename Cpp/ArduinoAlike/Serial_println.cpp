#include <iostream>
#include <string>

class SerialClass {
public:
    template <typename T>
    void print(const T& data) {
        std::cout << data;
    }

    template <typename T>
    void println(const T& data) {
        std::cout << data << std::endl;
    }

    // Overloads for print with no arguments to just start a new line
    void println() {
        std::cout << std::endl;
    }
};

// Instantiate a global Serial object similar to Arduino
SerialClass Serial;

int main() {
    Serial.print("Hello, ");
    Serial.print("World!");
    Serial.println();  // Equivalent to Serial.println() in Arduino, just moves to the next line
    Serial.println(123);  // Print an integer
    Serial.println(45.67);  // Print a floating-point number
    Serial.println('A');  // Print a single character
    Serial.println(true);  // Print a boolean value
    Serial.println("This is a string.");

    return 0;
}

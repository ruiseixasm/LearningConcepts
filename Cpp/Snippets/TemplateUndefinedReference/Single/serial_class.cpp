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

void SerialClass::begin(unsigned long int boud) {
    boud_rate = boud;
}

template <typename T>
void SerialClass::print(const T& data) {
    std::cout << "(" << boud_rate << ") : " << data;
}

template <typename T>
void SerialClass::println(const T& data) {
    std::cout << "(" << boud_rate << ") : " << data << std::endl;
}

void SerialClass::println() {
    std::cout << "(" << boud_rate << ") : " << std::endl;
}

// Instantiate a global Serial object similar to Arduino
SerialClass Serial;

int main() {
    int number = 10;
    Serial.println(number);


    return 0;
}
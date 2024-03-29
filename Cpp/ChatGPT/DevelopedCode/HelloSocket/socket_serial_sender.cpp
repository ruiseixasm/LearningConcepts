#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

int main() {
    // Open the serial port file for writing
    std::ofstream serial("/dev/ttyUSB0");

    // Check if the serial port is open
    if (!serial.is_open()) {
        std::cerr << "Failed to open serial port." << std::endl;
        return 1;
    }

    // String to send
    std::string message = "Hello, Arduino!";

    // Write the message to the serial port
    serial << message;

    // Close the serial port
    serial.close();

    std::cout << "Message sent successfully." << std::endl;

    return 0;
}

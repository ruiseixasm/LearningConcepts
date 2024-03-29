#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

int main() {
    // Open the serial port
    std::ofstream serial("/dev/ttyUSB0");

    // Check if the port is open
    if (!serial.is_open()) {
        std::cerr << "Error: Unable to open serial port." << std::endl;
        return 1;
    }

    // String to send
    std::string message = "Hello, Arduino!";

    // Send the string to the serial port
    serial << message << std::endl;

    // Close the serial port
    serial.close();

    return 0;
}

// Check serial pots commands:
    // ls /dev/ttyS* /dev/ttyUSB*               // available serial ports
    // dmesg | grep tty                         // contain information about detected serial ports
    // udevadm info -a -n /dev/ttyUSB0          // provide detailed information about devices and their attributes

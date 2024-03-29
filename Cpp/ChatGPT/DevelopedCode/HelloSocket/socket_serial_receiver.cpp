#include <iostream>
#include <fstream>
#include <string>

int main() {
    // Open the serial port file for reading
    std::ifstream serial("/dev/ttyUSB0");

    // Check if the serial port is open
    if (!serial.is_open()) {
        std::cerr << "Failed to open serial port." << std::endl;
        return 1;
    }

    // Read data from the serial port
    std::string receivedData;
    std::getline(serial, receivedData);

    // Close the serial port
    serial.close();

    // Print the received data
    std::cout << "Received message: " << receivedData << std::endl;

    return 0;
}

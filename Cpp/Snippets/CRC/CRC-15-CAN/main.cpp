#include <iostream>
#include <vector>
#include "CRC-15-CAN.h"

int main() {
    // Original data
    std::vector<uint8_t> data = {0x32, 0x91, 0x11, 0x92, 0x77, 0x46, 0x85, 0x24};

    // Compute CRC-15-CAN for the data
    uint16_t crc = CRC15CAN::compute(data);
    std::cout << "Computed CRC: " << std::hex << crc << std::dec << std::endl;

    // Simulate data corruption
    data[2] ^= 0x01; // Flip a bit to introduce an error

    // Verify data with received CRC
    if (CRC15CAN::verify(data, crc)) {
        std::cout << "Data is correct." << std::endl;
    } else {
        std::cout << "Data is corrupted. Attempting to correct..." << std::endl;
        if (CRC15CAN::correct(data, crc)) {
            std::cout << "Data corrected successfully." << std::endl;
        } else {
            std::cout << "Failed to correct data." << std::endl;
        }
    }

    // Print the (corrected) data
    std::cout << "Data: ";
    for (uint8_t byte : data) {
        std::cout << std::hex << static_cast<int>(byte) << " ";
    }
    std::cout << std::dec << std::endl;

    return 0;
}

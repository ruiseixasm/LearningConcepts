#include <iostream>
#include "ReedSolomon.h"

int main() {
    // Original data
    std::vector<int> data = { 32, 91, 11, 92, 77, 46, 85, 24, 19, 81, 72, 43, 60, 59, 16, 7 };

    // Encode data with Reed-Solomon (adding 10 parity symbols)
    int nsym = 10;
    std::vector<int> encoded_data = ReedSolomon::encode(data, nsym);
    std::cout << "Encoded data: ";
    for (int byte : encoded_data) {
        std::cout << byte << " ";
    }
    std::cout << std::endl;

    // Simulate data corruption
    encoded_data[2] = 99; // Corrupting one byte
    encoded_data[5] = 88; // Corrupting another byte

    // Decode data
    bool success = ReedSolomon::decode(encoded_data, nsym);
    if (success) {
        std::cout << "Decoded data: ";
        for (int byte : encoded_data) {
            std::cout << byte << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Failed to decode data." << std::endl;
    }

    return 0;
}

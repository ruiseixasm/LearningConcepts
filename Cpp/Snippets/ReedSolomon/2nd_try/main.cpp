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

    // Introduce some errors in the encoded data
    encoded_data[3] ^= 0xFF;  // Introduce an error
    encoded_data[8] ^= 0xFF;  // Introduce another error

    std::cout << "Encoded data with errors: ";
    for (int byte : encoded_data) {
        std::cout << byte << " ";
    }
    std::cout << std::endl;

    // Decode and correct the errors
    if (ReedSolomon::decode(encoded_data, nsym)) {
        std::cout << "Decoded and corrected data: ";
        for (int byte : encoded_data) {
            std::cout << byte << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Failed to decode and correct data." << std::endl;
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

// Function to compute the CRC-8
uint8_t computeCRC8(const vector<uint8_t>& data) {
    uint8_t crc = 0x00;
    uint8_t polynomial = 0x07; // CRC-8 polynomial

    for (size_t i = 0; i < data.size(); ++i) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; ++j) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ polynomial;
            } else {
                crc <<= 1;
            }
        }
    }

    return crc;
}

// Function to simulate transmission error by flipping a bit
void introduceError(vector<uint8_t>& data) {
    data[2] ^= 0x01; // Flip the least significant bit of the third byte
}

int main() {
    // Example data: "Hello"
    vector<uint8_t> data = {'H', 'e', 'l', 'l', 'o'};
    
    // Compute the CRC-8 for the data
    uint8_t crc = computeCRC8(data);
    
    // Append CRC to the data
    data.push_back(crc);
    
    cout << "Original data with CRC: ";
    for (uint8_t byte : data) {
        cout << bitset<8>(byte) << " ";
    }
    cout << endl;

    // Simulate a transmission error
    introduceError(data);

    cout << "Data with error: ";
    for (uint8_t byte : data) {
        cout << bitset<8>(byte) << " ";
    }
    cout << endl;

    // Separate the received data and received CRC
    vector<uint8_t> receivedData(data.begin(), data.end() - 1);
    uint8_t receivedCRC = data.back();

    // Compute CRC on the received data
    uint8_t computedCRC = computeCRC8(receivedData);

    // Check if the received CRC matches the computed CRC
    if (computedCRC == receivedCRC) {
        cout << "No error detected." << endl;
    } else {
        cout << "Error detected!" << endl;
    }

    return 0;
}

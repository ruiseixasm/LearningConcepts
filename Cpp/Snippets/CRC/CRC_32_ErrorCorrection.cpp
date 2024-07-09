#include <iostream>
#include <vector>
#include <bitset>
#include <cstdint>

using namespace std;

const uint32_t CRC32_POLYNOMIAL = 0xEDB88320;

uint32_t crc32(const vector<uint8_t>& data) {
    uint32_t crc = 0xFFFFFFFF;

    for (uint8_t byte : data) {
        crc ^= byte;
        for (int i = 0; i < 8; ++i) {
            if (crc & 1)
                crc = (crc >> 1) ^ CRC32_POLYNOMIAL;
            else
                crc >>= 1;
        }
    }

    return ~crc;
}

vector<uint8_t> encodeData(const vector<uint8_t>& data) {
    vector<uint8_t> encodedData = data;

    uint32_t crc = crc32(data);
    for (int i = 0; i < 4; ++i) {
        encodedData.push_back(crc & 0xFF);
        crc >>= 8;
    }

    return encodedData;
}

void introduceError(vector<uint8_t>& data, size_t position) {
    data[position] ^= 0xFF; // Introduce a byte error
}

bool checkAndCorrectData(vector<uint8_t>& data) {
    if (data.size() < 4) return false;

    vector<uint8_t> originalData(data.begin(), data.end() - 4);
    uint32_t receivedCrc = 0;
    for (int i = 0; i < 4; ++i) {
        receivedCrc |= (data[data.size() - 4 + i] << (8 * i));
    }

    uint32_t computedCrc = crc32(originalData);
    if (receivedCrc == computedCrc) {
        cout << "No error detected." << endl;
        return true;
    } else {
        cout << "Error detected!" << endl;
        uint32_t syndrome = computedCrc ^ receivedCrc;

        // Try to correct single-bit errors
        for (size_t i = 0; i < originalData.size(); ++i) {
            for (uint8_t bit = 0; bit < 8; ++bit) {
                originalData[i] ^= (1 << bit);
                if (crc32(originalData) == receivedCrc) {
                    cout << "Single-bit error corrected at byte " << i << ", bit " << static_cast<int>(bit) << endl;
                    data = originalData;
                    uint32_t newCrc = crc32(originalData);
                    for (int j = 0; j < 4; ++j) {
                        data.push_back(newCrc & 0xFF);
                        newCrc >>= 8;
                    }
                    return true;
                }
                originalData[i] ^= (1 << bit);
            }
        }
    }

    cout << "Error could not be corrected." << endl;
    return false;
}

int main() {
    // Original data (8 bytes)
    vector<uint8_t> data = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};

    // Encode data with CRC-32
    vector<uint8_t> encodedData = encodeData(data);

    cout << "Encoded data: ";
    for (uint8_t byte : encodedData) {
        cout << bitset<8>(byte) << " ";
    }
    cout << endl;

    // Introduce a single-byte error
    introduceError(encodedData, 5);

    cout << "Data with error: ";
    for (uint8_t byte : encodedData) {
        cout << bitset<8>(byte) << " ";
    }
    cout << endl;

    // Check and correct errors
    bool isCorrect = checkAndCorrectData(encodedData);

    if (isCorrect) {
        cout << "Corrected data: ";
        for (uint8_t byte : encodedData) {
            cout << bitset<8>(byte) << " ";
        }
        cout << endl;
    }

    return 0;
}

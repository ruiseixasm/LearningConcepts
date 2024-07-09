#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

// Function to calculate the CRC remainder
vector<int> computeCRC(const vector<int>& data, const vector<int>& polynomial) {
    vector<int> dataWithZeros = data;
    dataWithZeros.resize(data.size() + polynomial.size() - 1, 0);

    for (size_t i = 0; i < data.size(); ++i) {
        if (dataWithZeros[i] == 1) {
            for (size_t j = 0; j < polynomial.size(); ++j) {
                dataWithZeros[i + j] ^= polynomial[j];
            }
        }
    }

    vector<int> remainder(dataWithZeros.end() - (polynomial.size() - 1), dataWithZeros.end());
    return remainder;
}

// Function to encode data with CRC
vector<int> encodeData(const vector<int>& data, const vector<int>& polynomial) {
    vector<int> encodedData = data;
    vector<int> crc = computeCRC(data, polynomial);
    encodedData.insert(encodedData.end(), crc.begin(), crc.end());
    return encodedData;
}

// Function to introduce a single-bit error
void introduceError(vector<int>& data, size_t position) {
    data[position] ^= 1;
}

// Function to check and correct errors
vector<int> checkAndCorrectData(vector<int> data, const vector<int>& polynomial) {
    vector<int> remainder = computeCRC(data, polynomial);

    // Convert remainder to an integer to find error position
    int errorPosition = 0;
    for (size_t i = 0; i < remainder.size(); ++i) {
        if (remainder[i] == 1) {
            errorPosition += (1 << (remainder.size() - 1 - i));
        }
    }

    if (errorPosition > 0 && errorPosition <= data.size()) {
        cout << "Error detected at position: " << errorPosition - 1 << endl;
        data[errorPosition - 1] ^= 1; // Correct the error
    } else {
        cout << "No error detected." << endl;
    }

    return data;
}

int main() {
    // Original data (8 bits)
    vector<int> data = {1, 0, 1, 0, 1, 1, 0, 0};

    // CRC-8-Bluetooth polynomial (x^8 + x^7 + x^6 + x^4 + x^2 + 1)
    vector<int> polynomial = {1, 1, 0, 1, 0, 1, 0, 1, 1};

    // Encode data with CRC
    vector<int> encodedData = encodeData(data, polynomial);

    cout << "Encoded data: ";
    for (int bit : encodedData) {
        cout << bit;
    }
    cout << endl;

    // Introduce a single-bit error
    introduceError(encodedData, 5);

    cout << "Data with error: ";
    for (int bit : encodedData) {
        cout << bit;
    }
    cout << endl;

    // Check and correct errors
    vector<int> correctedData = checkAndCorrectData(encodedData, polynomial);

    cout << "Corrected data: ";
    for (int bit : correctedData) {
        cout << bit;
    }
    cout << endl;

    return 0;
}

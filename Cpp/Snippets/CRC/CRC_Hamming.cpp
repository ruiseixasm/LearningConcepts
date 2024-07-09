#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

// Function to compute the Hamming (7,4) code
vector<int> encodeHamming(vector<int> data) {
    vector<int> encoded(7);

    // Data bits
    encoded[2] = data[0];
    encoded[4] = data[1];
    encoded[5] = data[2];
    encoded[6] = data[3];

    // Parity bits
    encoded[0] = data[0] ^ data[1] ^ data[3];
    encoded[1] = data[0] ^ data[2] ^ data[3];
    encoded[3] = data[1] ^ data[2] ^ data[3];

    return encoded;
}

// Function to introduce a single-bit error
void introduceError(vector<int>& encoded) {
    encoded[3] ^= 1; // Flip the 4th bit
}

// Function to detect and correct a single-bit error in Hamming (7,4) code
vector<int> decodeHamming(vector<int> encoded) {
    // Calculate parity bits
    int p1 = encoded[0] ^ encoded[2] ^ encoded[4] ^ encoded[6];
    int p2 = encoded[1] ^ encoded[2] ^ encoded[5] ^ encoded[6];
    int p3 = encoded[3] ^ encoded[4] ^ encoded[5] ^ encoded[6];

    // Determine error position
    int errorPosition = p1 * 1 + p2 * 2 + p3 * 4;

    if (errorPosition != 0) {
        cout << "Error detected at position: " << errorPosition << endl;
        // Correct the error
        encoded[errorPosition - 1] ^= 1;
    } else {
        cout << "No error detected." << endl;
    }

    // Extract the original data bits
    vector<int> data(4);
    data[0] = encoded[2];
    data[1] = encoded[4];
    data[2] = encoded[5];
    data[3] = encoded[6];

    return data;
}

int main() {
    // Original 4-bit data
    vector<int> data = {1, 0, 1, 1};

    // Encode the data using Hamming (7,4) code
    vector<int> encoded = encodeHamming(data);

    cout << "Encoded data: ";
    for (int bit : encoded) {
        cout << bit;
    }
    cout << endl;

    // Introduce a single-bit error
    introduceError(encoded);

    cout << "Data with error: ";
    for (int bit : encoded) {
        cout << bit;
    }
    cout << endl;

    // Decode the data and correct the error
    vector<int> decoded = decodeHamming(encoded);

    cout << "Corrected data: ";
    for (int bit : decoded) {
        cout << bit;
    }
    cout << endl;

    return 0;
}

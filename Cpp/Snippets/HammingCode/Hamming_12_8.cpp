#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to calculate the parity bits and generate the Hamming code
vector<int> calculateParityBits(vector<int>& data) {
    int n = data.size();
    int r = 4; // For Hamming (12,8)

    // Create a vector to hold the data and parity bits
    vector<int> hammingCode(n + r, 0);

    // Place the data bits
    int j = 0;
    for (int i = 0; i < n + r; i++) {
        if ((i + 1) != pow(2, j)) {
            hammingCode[i] = data[i - j];
        } else {
            j++;
        }
    }

    // Calculate the parity bits
    for (int i = 0; i < r; i++) {
        int position = pow(2, i);
        int parity = 0;
        for (int k = 0; k < n + r; k++) {
            if ((k + 1) & position) {
                parity ^= hammingCode[k];
            }
        }
        hammingCode[position - 1] = parity;
    }

    return hammingCode;
}

// Function to detect and correct errors
void detectAndCorrectErrors(vector<int>& hammingCode) {
    int r = 4; // For Hamming (12,8)
    int n = hammingCode.size();

    // Calculate the error position
    int errorPosition = 0;
    for (int i = 0; i < r; i++) {
        int position = pow(2, i);
        int parity = 0;
        for (int k = 0; k < n; k++) {
            if ((k + 1) & position) {
                parity ^= hammingCode[k];
            }
        }
        if (parity != 0) {
            errorPosition += position;
        }
    }

    // If an error is detected, correct it
    if (errorPosition != 0) {
        cout << "Error detected at position: " << errorPosition << endl;
        hammingCode[errorPosition - 1] ^= 1;
        cout << "Error corrected." << endl;
    } else {
        cout << "No error detected." << endl;
    }
}

// Function to extract the original data from the Hamming code
vector<int> extractData(vector<int>& hammingCode) {
    int n = hammingCode.size();
    int r = 4; // For Hamming (12,8)

    // Extract the data bits
    vector<int> data;
    int j = 0;
    for (int i = 0; i < n; i++) {
        if ((i + 1) != pow(2, j)) {
            data.push_back(hammingCode[i]);
        } else {
            j++;
        }
    }

    return data;
}

int main() {
    // Example data: 10110011 (8 bits)
    vector<int> data = {1, 0, 1, 1, 0, 0, 1, 1};

    // Encode the data using Hamming (12,8) Code
    vector<int> hammingCode = calculateParityBits(data);

    // Print the encoded data
    cout << "Encoded data: ";
    for (int i = 0; i < hammingCode.size(); i++) {
        cout << hammingCode[i] << " ";
    }
    cout << endl;

    // Introduce an error for testing (flip a bit)
    hammingCode[2] ^= 1;  // Flip the bit at position 3 (index 2)
    cout << "Data with error: ";
    for (int i = 0; i < hammingCode.size(); i++) {
        cout << hammingCode[i] << " ";
    }
    cout << endl;

    // Detect and correct errors
    detectAndCorrectErrors(hammingCode);

    // Print the corrected data
    cout << "Corrected data: ";
    for (int i = 0; i < hammingCode.size(); i++) {
        cout << hammingCode[i] << " ";
    }
    cout << endl;

    // Extract the original data from the Hamming code
    vector<int> originalData = extractData(hammingCode);

    // Print the original data
    cout << "Original data: ";
    for (int bit : originalData) {
        cout << bit << " ";
    }
    cout << endl;

    return 0;
}

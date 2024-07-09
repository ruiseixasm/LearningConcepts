#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to calculate the parity bits
vector<int> calculateParityBits(vector<int>& data) {
    int n = data.size();
    int r = 0;

    // Calculate the number of parity bits needed
    while (pow(2, r) < n + r + 1) {
        r++;
    }

    // Create a vector to hold the data and parity bits
    vector<int> hammingCode(n + r + 1, 0);

    // Place the data bits and leave space for parity bits
    int j = 0;
    for (int i = 1; i <= n + r; i++) {
        if (i == pow(2, j)) {
            j++;
        } else {
            hammingCode[i] = data[i - j - 1];
        }
    }

    // Calculate the parity bits
    for (int i = 0; i < r; i++) {
        int position = pow(2, i);
        int parity = 0;
        for (int k = 1; k <= n + r; k++) {
            if (k & position) {
                parity ^= hammingCode[k];
            }
        }
        hammingCode[position] = parity;
    }

    return hammingCode;
}

// Function to detect and correct errors
void detectAndCorrectErrors(vector<int>& hammingCode) {
    int r = 0;
    int n = hammingCode.size() - 1;

    // Calculate the number of parity bits
    while (pow(2, r) < n + 1) {
        r++;
    }

    // Calculate the error position
    int errorPosition = 0;
    for (int i = 0; i < r; i++) {
        int position = pow(2, i);
        int parity = 0;
        for (int k = 1; k <= n; k++) {
            if (k & position) {
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
        hammingCode[errorPosition] ^= 1;
        cout << "Error corrected." << endl;
    } else {
        cout << "No error detected." << endl;
    }
}

// Function to extract the original data from the hamming code
vector<int> extractData(vector<int>& hammingCode) {
    int n = hammingCode.size() - 1;
    int r = 0;

    // Calculate the number of parity bits
    while (pow(2, r) < n + 1) {
        r++;
    }

    // Extract the data bits
    vector<int> data;
    int j = 0;
    for (int i = 1; i <= n; i++) {
        if (i == pow(2, j)) {
            j++;
        } else {
            data.push_back(hammingCode[i]);
        }
    }

    return data;
}

int main() {
    // Example data: 1011
    vector<int> data = {1, 0, 1, 1};

    // Encode the data using Hamming Code
    vector<int> hammingCode = calculateParityBits(data);

    // Print the encoded data
    cout << "Encoded data: ";
    for (int i = 1; i < hammingCode.size(); i++) {
        cout << hammingCode[i] << " ";
    }
    cout << endl;

    // Introduce an error for testing
    hammingCode[3] ^= 1;
    cout << "Data with error: ";
    for (int i = 1; i < hammingCode.size(); i++) {
        cout << hammingCode[i] << " ";
    }
    cout << endl;

    // Detect and correct errors
    detectAndCorrectErrors(hammingCode);

    // Print the corrected data
    cout << "Corrected data: ";
    for (int i = 1; i < hammingCode.size(); i++) {
        cout << hammingCode[i] << " ";
    }
    cout << endl;

    // Extract the original data from the hamming code
    vector<int> originalData = extractData(hammingCode);

    // Print the original data
    cout << "Original data: ";
    for (int bit : originalData) {
        cout << bit << " ";
    }
    cout << endl;

    return 0;
}

#include <windows.h>
#include <cstdlib>
#include <ctime>

int lastRandomNumber = -1;      // Stores the last generated random number
bool newValueAvailable = false; // Flag to indicate if a new random value is available
DWORD generationStartTime = 0;  // Start time for delay
int randomDelay = 0;            // Random delay duration in milliseconds

extern "C" __declspec(dllexport) void StartRandomNumberGeneration() {
    // Seed the random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    // Set a random delay between 1 and 5 seconds
    randomDelay = (rand() % 5 + 1) * 1000;

    // Record the start time for the delay
    generationStartTime = GetTickCount();

    // Reset the flag
    newValueAvailable = false;
}

extern "C" __declspec(dllexport) void CheckRandomNumberGeneration() {
    // Check if the delay period has elapsed
    if (GetTickCount() - generationStartTime >= (DWORD)randomDelay && !newValueAvailable) {
        // Generate the random number
        lastRandomNumber = rand();
        newValueAvailable = true; // Mark the new value as available
    }
}

extern "C" __declspec(dllexport) int GetLastRandomNumber() {
    newValueAvailable = false; // Reset the flag
    return lastRandomNumber;
}

extern "C" __declspec(dllexport) bool IsNewValueAvailable() {
    return newValueAvailable;
}

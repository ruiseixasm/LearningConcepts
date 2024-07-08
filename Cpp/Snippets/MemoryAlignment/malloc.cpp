#include <iostream>
#include <cstdlib>

int main() {
    // Allocate memory for an array of 10 integers without alignment
    size_t size = 10 * sizeof(int);
    
    // Allocate unaligned memory
    int* unalignedArray = (int*)malloc(size);

    if (unalignedArray == nullptr) {
        std::cerr << "Unaligned memory allocation failed" << std::endl;
        return 1;
    }

    // Use the unaligned array
    for (int i = 0; i < 10; ++i) {
        unalignedArray[i] = i * 10;
        std::cout << "Unaligned array element " << i << ": " << unalignedArray[i] << std::endl;
    }

    // Free the allocated memory
    free(unalignedArray);

    return 0;
}

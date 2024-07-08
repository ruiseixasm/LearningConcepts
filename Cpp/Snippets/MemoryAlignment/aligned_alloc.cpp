#include <iostream>
#include <cstdlib> // For std::aligned_alloc and free

int main() {
    // Allocate memory for an array of 10 integers with alignment
    size_t alignment = alignof(int);
    size_t size = 10 * sizeof(int);
    
    // Allocate aligned memory
    int* alignedArray = (int*)std::aligned_alloc(alignment, size);

    if (alignedArray == nullptr) {
        std::cerr << "Aligned memory allocation failed" << std::endl;
        return 1;
    }

    // Use the aligned array
    for (int i = 0; i < 10; ++i) {
        alignedArray[i] = i * 10;
        std::cout << "Aligned array element " << i << ": " << alignedArray[i] << std::endl;
    }

    // Free the allocated memory
    free(alignedArray);

    return 0;
}

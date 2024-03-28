#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Iterate over each element in the vector using a range-based for loop with a reference
    for (int& number : numbers) {
        number *= 2; // Modify each element by doubling its value
    }

    // Print the modified vector
    for (int number : numbers) {
        std::cout << number << " ";
    }   // 2 4 6 8 10

    std::cout << std::endl;
    
    return 0;
}

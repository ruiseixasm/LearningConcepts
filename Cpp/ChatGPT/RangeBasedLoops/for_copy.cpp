#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Iterate over each element in the vector using a range-based for loop
    for (int number : numbers) {
        std::cout << number << " ";
    }   // 1 2 3 4 5

    std::cout << std::endl;
    
    return 0;
}

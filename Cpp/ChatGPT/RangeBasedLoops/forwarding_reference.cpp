#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Iterate over each element in the vector using a range-based for loop with &&
    // Using auto&& in a range-based for loop allows for two-way reference collapsing,
    //     which is particularly useful for function parameters, among other scenarios.
    for (auto&& number : numbers) {
        std::cout << number << " ";
    }   // 1 2 3 4 5

    std::cout << std::endl;
    
    return 0;
}

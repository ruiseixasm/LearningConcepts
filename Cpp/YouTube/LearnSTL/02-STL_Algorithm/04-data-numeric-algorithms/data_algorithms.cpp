#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>    // for pow function
#include <deque>
#include <random>   // for default_random_engine()

using namespace std;

template<typename ContainerType>
void printContainer(const ContainerType& container) {
    // Deduce the value type of the container
    using T = typename ContainerType::value_type;

    // Determine the container type and print appropriate message
    if constexpr (std::is_same_v<ContainerType, std::set<T>>) { // constexpr forces evaluation at compile time
        std::cout << "Contents of the set:" << " ";
    } else if constexpr (std::is_same_v<ContainerType, std::multiset<T>>) {
        std::cout << "Contents of the multiset:" << " ";
    } else if constexpr (std::is_same_v<ContainerType, std::vector<T>>) {
        std::cout << "Contents of the vector:" << " ";
    } else if constexpr (std::is_same_v<ContainerType, std::deque<T>>) {
        std::cout << "Contents of the deque:" << " ";
    } else {
        std::cout << "Contents of the Container:" << " ";
    }

    // Iterate over the set using a range-based for loop
    for (const T& element : container) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

void printVectorIterator(std::vector<int>::iterator &itr, std::vector<int> &vec)
{
    // ALWAYS CHECK FOR UNDEFINED BEHAVIOR !!!
    if (itr != vec.end())
    {
        cout << "itr = " << *itr << endl;       // 33 (undefined behavior!!)
    }
    else
    {
        cout << "No such pair found." << endl;  // Output if no such pair exists
    }
}

int main() {
    /*
     * Sorted Data Algorithms
     *   - Algorithms that require data being pre-sorted
     *   - Binary search, merge, set operations
     */

    // Note: Every sorted data algorithm has a generalized form with the same name.

    {
        // 1. Binary search

        vector<int> vec = {8, 9, 9, 9, 45, 87, 90};     // 7 items

        bool vec_found = binary_search(vec.begin(), vec.end(), 9);  // check if 9 is in vec
        cout << "vec_found: " << vec_found << endl;     // vec_found: 1

        vector<int> s = {9, 45, 66};
        // Return true if all elements of s are included in vec
        // Both vec and s must be sorted
        vec_found = includes(vec.begin(), vec.end(),    // Range #1
                            s.begin(), s.end());        // Range #2
        cout << "vec_found: " << vec_found << endl;     // vec_found: 0
        
        // Search position
        // Find the first position where 9 could be inserted and still keep the sorting.
        auto itr = lower_bound(vec.begin(), vec.end(), 9);  // vec[1]
        printVectorIterator(itr, vec);                  // itr = 9

        // Find the last position where 9 could be inserted and still keep the sorting.
        itr = upper_bound(vec.begin(), vec.end(), 9);   // vec[4]
        printVectorIterator(itr, vec);                  // itr = 45

        // Returns both first and last position
        auto pair_of_itr = equal_range(vec.begin(), vec.end(), 9);
        printVectorIterator(pair_of_itr.first, vec);            // itr = 9
        printVectorIterator(pair_of_itr.second, vec);           // itr = 45
    }

    std::cout << std::endl;
    {
        // 2. Merge

        vector<int> vec = {8, 9, 9, 10};
        vector<int> vec2 = {7, 9, 10};
        vector<int> vec_out(8, 0);
        merge(vec.begin(), vec.end(),       // Input Range #1
                vec2.begin(), vec2.end(),   // Input Range #2
                vec_out.begin());           // Output
                // Both vec and vec2 should be sorted (same for the set operation)
                // Nothing is dropped, all duplicates are kept.
        printContainer(vec_out);            // 7 8 9 9 9 10 10 0

        vec = {1, 2, 3, 4, 1, 2, 3, 4, 5};  // Both parts of vec are already sorted
        //                 ^---- Split itr (vec.begin() + 4)
        // If the two ranges passed to inplace_merge aren't already sorted,
        //     the behavior of the function is undefined.
        // Merge the ranges [vec.begin(), vec.begin() + 4) and [vec.begin() + 4, vec.end())
        inplace_merge(vec.begin(), vec.begin() + 4, vec.end()); // - One step of merge sort
        printContainer(vec);                // 1 1 2 2 3 3 4 4 5

    }

    std::cout << std::endl;
    {
        // 3. Set operations

        vector<int> vec = {8, 9, 9, 10};
        vector<int> vec2 = {7, 9, 10};
        vector<int> vec_out(8, 0);

        // - Both vec and vec2 should be sorted
        // - The resulted data is also sorted
        set_union(vec.begin(), vec.end(),       // Input Range #1
                    vec2.begin(), vec2.end(),   // Input Range #2
                    vec_out.begin());           // Output
        // if X is in both vec and vec2, only one X is kept in vec_out
        printContainer(vec_out);                // 7 8 9 9 10 0 0 0
        
        vec_out = vector<int>(8, 0);

        set_intersection(vec.begin(), vec.end(),// Input Range #1
                    vec2.begin(), vec2.end(),   // Input Range #2
                    vec_out.begin());           // Output
        // Only items that are in both vec and vec2 are saved in vec_out
        printContainer(vec_out);                // 9 10 0 0 0 0 0 0

        vec_out = vector<int>(8, 0);

        set_difference(vec.begin(), vec.end(),  // Input Range #1
                    vec2.begin(), vec2.end(),   // Input Range #2
                    vec_out.begin());           // Output
        // Only the items that are in vec but NOT in vec2 are saved in vec_out
        printContainer(vec_out);                // 8 9 0 0 0 0 0 0

        vec_out = vector<int>(8, 0);

        set_symmetric_difference(vec.begin(), vec.end(),    // Input Range #1
                    vec2.begin(), vec2.end(),               // Input Range #2
                    vec_out.begin());                       // Output
        // Only mutually exclusive items from either vec or vec2 but not both.
        printContainer(vec_out);                // 7 8 9 0 0 0 0 0
    }

    return 0;
}
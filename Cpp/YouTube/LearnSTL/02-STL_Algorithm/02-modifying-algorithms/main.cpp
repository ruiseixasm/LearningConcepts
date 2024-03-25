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
     * Algorithm Walkthrough:
     *   Value-changing Algorithm - Changes the element values
     *   copy, movie, transform, swap, fill, replace, remove
     */

    std::cout << std::endl;
    {
        // 1. Copy

        vector<int> vec = {9, 60, 70, 8, 45, 87, 90};   // 7 items
        vector<int> vec2(11, 0);                        // 11 items (0 value)
        printContainer(vec2);                   // 0 0 0 0 0 0 0 0 0 0 0

        vector<int>::iterator itr, itr2;
        pair<vector<int>::iterator, vector<int>::iterator> pair_of_itr;

        // Checks that vec2 has sufficient capacity to accommodate the copied elements.
        if (vec.size() <= vec2.size()) {
            copy(vec.begin(), vec.end(),        // source
                vec2.begin());                  // destination
        }
        printContainer(vec2);                   // 9 60 70 8 45 87 90 0 0 0 0

        // This operation replaces the previous contents of vec2 with the new contents.
        // It does not cause memory leaks because the old memory associated with vec2
        //     is properly deallocated by the vector's assignment operator before
        //     the new memory is allocated.
        vec2 = vector<int>(11, 0);              // resets vec2 to zeroes (no memory leak)

        // Checks that vec2 has sufficient capacity to accommodate the copied elements.
        if (vec.size() <= vec2.size()) {
            copy_if(vec.begin(), vec.end(),     // source
                    vec2.begin(),               // destination
                    [](int x){return x > 80;}); // condition
        }
        printContainer(vec2);                   // 87 90 0 0 0 0 0 0 0 0 0

        vec2 = vector<int>(11, 0);              // resets vec2 to zeroes (no memory leak)

        int elements_to_copy = 4;
        // Checks that both vectors have sufficient capacity to accommodate the copied elements.
        if (vec.size() >= elements_to_copy && vec2.size() >= elements_to_copy)
            copy_n(vec.begin(), elements_to_copy, vec2.begin());
        printContainer(vec2);                   // 9 60 70 8 0 0 0 0 0 0 0

        vec2 = vector<int>(11, 0);              // resets vec2 to zeroes (no memory leak)

        // Checks that vec2 has sufficient capacity to accommodate the copied elements.
        if (vec.size() <= vec2.size()) {
            copy_backward(vec.begin(), vec.end(),   // source
                vec2.end());                        // destination
        }
        printContainer(vec2);                   // 0 0 0 0 9 60 70 8 45 87 90
    }

    std::cout << std::endl;
    {
        // 2. Move

        vector<string> vec = {"apple", "orange", "pear", "grape"};  // 4 items
        vector<string> vec2(6, "");                                 // 6 items ("" value)
        
        // vec: {"apple", "orange", "pear", "grape"}
        // vec2: {"", "", "", "", "", ""}   // Undefined
        //
        // If move semantics are defined for the element type, elements are moved over,
        // otherwise they are copied over with copy constructor, just like copy().

        // Checks that vec2 has sufficient capacity to accommodate the copied elements.
        if (vec.size() <= vec2.size())
            move(vec.begin(), vec.end(), vec2.begin());
        printContainer(vec);                    // (empty strings "")
        printContainer(vec2);                   // apple orange pear grape

        vec = {"", "banana", "", "mango"};      // 4 items (no memory leak)
        if (vec.size() <= vec2.size())
            move(vec.begin(), vec.end(), vec2.begin());
        printContainer(vec);                    // (empty strings "")
        printContainer(vec2);                   // "" banana "" mango

        vec = {"apple", "orange", "pear", "grape"}; // 4 items (no memory leak)
        vec2 = vector<string>(6, "");               // resets vec2 to "" (no memory leak)

        if (vec.size() <= vec2.size())
            move_backward(vec.begin(), vec.end(), vec2.end());
        printContainer(vec);                    // (empty strings "")
        printContainer(vec2);                   // "" "" apple orange pear grape
    }

    std::cout << std::endl;
    {
        // 3. Transform

        vector<int> vec = {9, 60, 70, 8, 45, 87, 80};   // 7 items
        vector<int> vec2 = {9, 60, 70, 8, 45, 87, 90};  // 7 items
        vector<int> vec3(11, 0);                        // 11 items all equal to 0

        if (vec.size() <= vec3.size())
            transform(vec.begin(), vec.end(),           // source
                    vec3.begin(),                       // destination
                    [](int x){return x - 1;});          // operation
        printContainer(vec);                            // 9 60 70 8 45 87 80
        printContainer(vec3);                           // 8 59 69 7 44 86 79 0 0 0 0

        vec3 = vector<int>(11, 0);                      // resets vec3 to zeroes (no memory leak)
        
        if (vec.size() <= vec3.size() && vec2.size() <= vec3.size())
            transform(vec.begin(), vec.end(),           // source #1
                    vec2.begin(),                       // source #2
                    vec3.begin(),                       // destination
                    [](int x, int y){return x + y;});   // operation
        printContainer(vec);                            // 9 60 70 8 45 87 80
        printContainer(vec2);                           // 9 60 70 8 45 87 90
        printContainer(vec3);                           // 18 120 140 16 90 174 170 0 0 0 0
    }

    std::cout << std::endl;
    {
        // 4. Swap - two way moving

        vector<string> vec = {"apple", "orange", "pear", "grape"};  // 4 items
        vector<string> vec2 = {"", "banana", "", "mango"};          // 4 items

        if (vec.size() == vec2.size())
            swap_ranges(vec.begin(), vec.end(), vec2.begin());
        printContainer(vec);                            // "" banana "" mango
        printContainer(vec2);                           // apple orange pear grape
    }

    std::cout << std::endl;
    {
        // 5. Fill

        vector<int> vec = {0, 0, 0, 0, 0};

        fill(vec.begin(), vec.end(), 9);
        printContainer(vec);                            // 9 9 9 9 9

        vec = {0, 0, 0, 0, 0};

        int elements_to_fill = 3;
        if (vec.size() >= elements_to_fill)
            fill_n(vec.begin(), elements_to_fill, 9);
        printContainer(vec);                            // 9 9 9 0 0

        vec = {0, 0, 0, 0, 0};

        generate(vec.begin(), vec.end(), rand);
        printContainer(vec);                            // 1804289383 846930886 1681692777 1714636915 1957747793

        vec = {0, 0, 0, 0, 0};

        if (vec.size() >= elements_to_fill)
            generate_n(vec.begin(), elements_to_fill, rand);
        printContainer(vec);                            // 424238335 719885386 1649760492 0 0
    }

    std::cout << std::endl;
    {
        // 6. Replace

        vector<int> vec = {9, 60, 70, 8, 45, 87, 90, 6};    // 8 items

        replace(vec.begin(), vec.end(),     // Data Range
            6,                              // Old value condition
            9);                             // New value
        printContainer(vec);                // 9 60 70 8 45 87 90 9

        vec = {9, 60, 70, 8, 45, 87, 90, 6};                // 8 items

        replace_if(vec.begin(), vec.end(),  // Data Range
            [](int x){return x > 80;},      // Old value condition
            9);                             // New value
        printContainer(vec);                // 9 60 70 8 45 9 9 6

        vec = {9, 60, 70, 8, 45, 87, 90, 6};                // 8 items
        vector<int> vec2 = {11, 3, 4, 6, 9, 4, 9, 2, 56};   // 9 items

        replace_copy(vec.begin(), vec.end(),    // Source
            vec2.begin(),                       // Destination
            6,                                  // Old value condition
            9);                                 // New value
        printContainer(vec);                // 9 60 70 8 45 87 90 6
        printContainer(vec2);               // 9 60 70 8 45 87 90 9 56
        // Generalized form: replace_copy_if()
    }

    std::cout << std::endl;
    {
        // 7. Remove

        vector<int> vec = {9, 6, 70, 8, 3, 87, 90, 6};      // 8 items
        vector<int> vec2(9, 0);                             // 9 items (all zeros)

        remove(vec.begin(), vec.end(), 3);      // Remove all 3's
        remove_copy(vec.begin(), vec.end(), vec2.begin(), 3);
        printContainer(vec);                    // 9 6 70 8 87 90 6 6
        printContainer(vec2);                   // 9 6 70 8 87 90 6 6 0

        vec = {9, 6, 70, 8, 3, 87, 90, 6};      // 8 items
        vec2 = vector<int>(9, 0);               // 9 items (all zeros)

        // Remove items bigger than 80
        remove_if(vec.begin(), vec.end(), [](int x){return x > 80;});
        remove_copy_if(vec.begin(), vec.end(), vec2.begin(), [](int x){return x > 80;});
        printContainer(vec);                    // 9 6 70 8 3 6 90 6
        printContainer(vec2);                   // 9 6 70 8 3 6 6 0 0

        vec = {9, 60, 70, 8, 3, 87, 90, 6};     // 8 items
        vec2 = vector<int>(9, 0);               // 9 items (all zeros)

        // Remove all 6's and copy the remaining items to vec2
        remove_copy(vec.begin(), vec.end(),     // Source
                    vec2.begin(),               // Destination
                    6);                         // Condition
        printContainer(vec);                    // 9 60 70 8 3 87 90 6
        printContainer(vec2);                   // 9 60 70 8 3 87 90 0 0
        // Generalized form: remove_copy_if()

        vec = {9, 60, 70, 8, 8, 87, 90, 60};                // 8 items
        vec2 = vector<int>(9, 0);               // 9 items (all zeros)

        // Remove consecutive equal elements
        unique(vec.begin(), vec.end());
        unique_copy(vec.begin(), vec.end(), vec2.begin());
        printContainer(vec);                    // 9 60 70 8 87 90 60 60
        printContainer(vec2);                   // 9 60 70 8 87 90 60 0 0

        vec = {9, 60, 70, 8, 3, 87, 90, 6};     // 8 items
        vec2 = vector<int>(9, 0);               // 9 items (all zeros)

        // Remove elements whose previous element is greater than itself
        unique(vec.begin(), vec.end(), less<int>());
        unique_copy(vec.begin(), vec.end(), vec2.begin(), less<int>());
        printContainer(vec);                    // 9 8 3 8 3 87 90 6
        printContainer(vec2);                   // 9 8 3 3 0 0 0 0 0

        vec = {9, 9, 70, 8, 8, 87, 90, 6};      // 8 items
        vec2 = vector<int>(9, 0);               // 9 items (all zeros)

        // Remove consecutive equal elements, and then copy the uniquified items to vec2
        unique_copy(vec.begin(), vec.end(), vec2.begin());
        printContainer(vec);                    // 9 9 70 8 8 87 90 6
        printContainer(vec2);                   // 9 70 8 87 90 6 0 0 0
        // Generalized form: unique_copy()
    }

    /*
     * Order-Changing Algorithms:
     *   - reverse, rotate, permute, shuffle
     * 
     * They change the order of elements in a container, but not necessarly the
     * elements themselves.
     */

    std::cout << std::endl;
    {
        // 1. Reverse

        vector<int> vec = {9, 60, 70, 8, 45, 87, 90};   // 7 items

        reverse(vec.begin() + 1, vec.end() - 1);
        printContainer(vec);                    // 9 87 45 8 70 60 90

        vec = {9, 60, 70, 8, 45, 87, 90};       // 7 items
        vector<int> vec2(7, 0);                 // 7 items (all zeroes)

        reverse_copy(vec.begin() + 1, vec.end() - 1, vec2.begin());
        printContainer(vec);                    // 9 60 70 8 45 87 90
        printContainer(vec2);                   // 87 45 8 70 60 0 0
    }

    std::cout << std::endl;
    {
        // 2. Rotate

        vector<int> vec = {9, 60, 70, 8, 45, 87, 90};   // 7 items

        rotate(vec.begin(), vec.begin() + 3, vec.end());
        printContainer(vec);                    // 8 45 87 90 9 60 70

        vec = {9, 60, 70, 8, 45, 87, 90};       // 7 items
        vector<int> vec2(7, 0);                 // 7 items (all zeroes)

        // Copy vec to vec2 in rotated order
        // vec is unchanged
        rotate_copy(vec.begin(), vec.begin() + 3, vec.end(),    // Source
                    vec2.begin());                              // Destination
        printContainer(vec);                    // 9 60 70 8 45 87 90
        printContainer(vec2);                   // 8 45 87 90 9 60 70
    }

    std::cout << std::endl;
    {
        // 3. Permute

        vector<int> vec = {9, 60, 70, 8, 45, 87, 90};   // 7 items

        // Lexicographical order, also known as dictionary order or alphabetical order,
        //     is a way of ordering sequences of elements (such as characters or numbers)
        //     based on their dictionary-like ordering. (Probabilistic permutations)

        // Lexicographically next greater permutation
        next_permutation(vec.begin(), vec.end());
        printContainer(vec);                    // 9 60 70 8 45 90 87

        vec = {9, 60, 70, 8, 45, 87, 90};       // 7 items

        // Lexicographically next smaller permutation
        prev_permutation(vec.begin(), vec.end());
        printContainer(vec);                    // 9 60 45 90 87 70 8
        // Generakized form: next_permutation(), prev_permutation()

        vector<int> permuted_vec = {1, 2, 3};   // 3 items
        do {
            printContainer(permuted_vec);
        } while (next_permutation(permuted_vec.begin(), permuted_vec.end()));
        // Contents of the vector: 1 2 3 
        // Contents of the vector: 1 3 2 
        // Contents of the vector: 2 1 3 
        // Contents of the vector: 2 3 1 
        // Contents of the vector: 3 1 2 
        // Contents of the vector: 3 2 1 
        
        prev_permutation(permuted_vec.begin(), permuted_vec.end());
        do {
            printContainer(permuted_vec);
        } while (prev_permutation(permuted_vec.begin(), permuted_vec.end()));
        // Contents of the vector: 3 2 1 
        // Contents of the vector: 3 1 2 
        // Contents of the vector: 2 3 1 
        // Contents of the vector: 2 1 3 
        // Contents of the vector: 1 3 2 
        // Contents of the vector: 1 2 3 
    }

    std::cout << std::endl;
    {
        // 4. Shuffle

        vector<int> vec = {9, 60, 70, 8, 45, 87, 90};   // 7 items

        //    - Rearrange the elements randomly
        //      (swap each element with a randomly selected element)
        random_shuffle(vec.begin(), vec.end());
        printContainer(vec);                    // 9 70 87 60 90 45 8

        // The error you're encountering is likely due to the fact that
        //     std::random_shuffle has been deprecated and removed in newer versions of C++,
        //     starting from C++14. Instead, you should use std::shuffle.
        // vec = {9, 60, 70, 8, 45, 87, 90};       // 7 items
        // random_shuffle(vec.begin(), vec.end(), rand);
        // printContainer(vec);                    // 9 60 45 90 87 70 8

        // C++ 11
        // Better random number generation (Modern Approach)
        vec = {9, 60, 70, 8, 45, 87, 90};       // 7 items
        shuffle(vec.begin(), vec.end(), default_random_engine());
        printContainer(vec);                    // 8 9 45 90 87 60 70
    }

    return 0;
}
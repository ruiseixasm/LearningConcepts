#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>    // for pow function
#include <deque>

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

    {
        // 4. Swap - two way moving

        vector<string> vec = {"apple", "orange", "pear", "grape"};  // 4 items
        vector<string> vec2 = {"", "banana", "", "mango"};          // 4 items

        if (vec.size() == vec2.size())
            swap_ranges(vec.begin(), vec.end(), vec2.begin());
        printContainer(vec);                            // "" banana "" mango
        printContainer(vec2);                           // apple orange pear grape
    }

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

    return 0;
}
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

int main() {

    /*
     * STL Algorithm Walkthrough:
     *     Non-modifying Algorithms
     *     count, min and max, compare, linear search, attribute
     */

    {
        vector<int> vec = {9, 60, 90, 8, 45, 90, 69, 55, 7};
        int num = count_if(vec.begin(), vec.end(), [](int x){return x < 10;});
        cout << "count_if total: " << num << endl;

        vector<int> vec2 = {9, 60, 70, 8, 45, 87};
        vector<int>::iterator itr, itr2;
        pair<vector<int>::iterator, vector<int>::iterator> pair_of_itr;
    }

    {
        vector<int> vec = {9, 60, 90, 8, 45, 87, 90, 69, 69, 55, 7};

        // 1. Counting
        //      Algorithm   Data            Operation
        int n = count(vec.begin() + 2, vec.end() - 1, 69);      // 2
        int m = count_if(vec.begin(), vec.end(),
                [](int x){return x < 10;});                     // 3
        cout << "n = " << n << ", m = " << m << endl;

        // 2. Min and Max
        auto itr = max_element(vec.begin() + 2, vec.end());     // 90
        cout << "itr = " << *itr << endl;

        // It returns the first max value
        itr = max_element(vec.begin(), vec.end(),
                    [](int x, int y){return x%10 < y%10;});     // 9
        cout << "itr = " << *itr << endl;

        // Most algorithms have a simple form and a generalized form

        // Generalized form: min_element()
        itr = min_element(vec.begin(), vec.end());              // 7
        cout << "itr = " << *itr << endl;

        // returns a pair, which contains first of min and last of max
        auto pair_of_itr = minmax_element(vec.begin(), vec.end(),
                    [](int x, int y){return x%10 < y%10;});     // {60, 69}
        cout << "pair_of_itr = {" << *(pair_of_itr.first) << ", " << *(pair_of_itr.second) << "}" << endl;
    }

    {
        vector<int> vec = {9, 60, 90, 8, 45, 45, 87, 90, 69, 69, 55, 7, 348, 276, 276};

        // 3. Linear Searching (used when data is not sorted)
        //    Returns the first match
        auto itr = find(vec.begin(), vec.end(), 55);
        cout << "itr = " << *itr << endl;                       // 55

        itr = find_if(vec.begin(), vec.end(), [](int x){return x > 80;});
        cout << "itr = " << *itr << endl;                       // 90

        itr = find_if_not(vec.begin(), vec.end(), [](int x){return x > 80;});
        cout << "itr = " << *itr << endl;                       // 9

        // Generalized form: search_n()
        itr = search_n(vec.begin(), vec.end(), 2, 69);  // Consecutive 2 items of 69
        cout << "itr = " << *itr << endl;                       // 69

        // Search subrange
        vector<int> sub = {45, 87, 90};
        // Generalized form: search(), find_end()
            // search first subrange (stops scanning on the first occurrence)
        itr = search(vec.begin(), vec.end(), sub.begin(), sub.end());
        cout << "itr = " << *itr << endl;                       // 45
            // search last subrange (scans the entire subrange and returns the latter position)
        itr = find_end(vec.begin(), vec.end(), sub.begin(), sub.end());
        cout << "itr = " << *itr << endl;                       // 45

        // Search any_of
        vector<int> items = {87, 69};
            // Search any one of the item in items
        itr = find_first_of(vec.begin(), vec.end(), items.begin(), items.end());
        cout << "itr = " << *itr << endl;                       // 87
            // Search any one of the item in the items that satisfy: x == 4*y
        itr = find_first_of(vec.begin(), vec.end(), items.begin(), items.end(),
                        [](int x, int y){return x == 4*y;});
        cout << "itr = " << *itr << endl;                       // 348

        // Search Adjacent
            // find two adjacent items that are the same
        itr = adjacent_find(vec.begin(), vec.end());
        cout << "itr = " << *itr << endl;                       // 69
            // find two adjacent items that satisfy: x == 4*y
        itr = adjacent_find(vec.begin(), vec.end(), [](int x, int y){return x == 4*y;});
        // ALWAYS CHECK FOR UNDEFINED BEHAVIOR !!!
        if (itr != vec.end()) {
            cout << "itr = " << *itr << endl;                   // 33 (undefined behavior!!)
        } else {
            cout << "No such pair found." << endl;  // Output if no such pair exists
        }
    }

    return 0;
}
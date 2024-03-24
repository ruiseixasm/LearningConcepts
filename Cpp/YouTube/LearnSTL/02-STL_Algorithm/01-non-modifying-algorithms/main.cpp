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
        auto itr = max_element(vec.begin() + 2, vec.end());
        printVectorIterator(itr, vec);                          // 90

        // It returns the first max value
        itr = max_element(vec.begin(), vec.end(),
                    [](int x, int y){return x%10 < y%10;});
        printVectorIterator(itr, vec);                          // 9

        // Most algorithms have a simple form and a generalized form

        // Generalized form: min_element()
        itr = min_element(vec.begin(), vec.end());
        printVectorIterator(itr, vec);                          // 7

        // returns a pair, which contains first of min and last of max
        auto pair_of_itr = minmax_element(vec.begin(), vec.end(),
                    [](int x, int y){return x%10 < y%10;});     // {60, 69}
        cout << "pair_of_itr = {" << *(pair_of_itr.first) << ", " << *(pair_of_itr.second) << "}" << endl;
    }

    {
        // 3. Linear Searching (used when data is not sorted)

        vector<int> vec = {9, 60, 90, 8, 45, 45, 87, 90, 69, 69, 55, 7, 348, 276, 276};

        //    Returns the first match
        auto itr = find(vec.begin(), vec.end(), 55);
        printVectorIterator(itr, vec);                          // 55

        itr = find_if(vec.begin(), vec.end(), [](int x){return x > 80;});
        printVectorIterator(itr, vec);                          // 90

        itr = find_if_not(vec.begin(), vec.end(), [](int x){return x > 80;});
        printVectorIterator(itr, vec);                          // 9

        // Generalized form: search_n()
        itr = search_n(vec.begin(), vec.end(), 2, 69);  // Consecutive 2 items of 69
        printVectorIterator(itr, vec);                          // 69

        // Search subrange
        vector<int> sub = {45, 87, 90};
        // Generalized form: search(), find_end()
            // search first subrange (stops scanning on the first occurrence)
        itr = search(vec.begin(), vec.end(), sub.begin(), sub.end());
        printVectorIterator(itr, vec);                          // 45
            // search last subrange (scans the entire subrange and returns the latter position)
        itr = find_end(vec.begin(), vec.end(), sub.begin(), sub.end());
        printVectorIterator(itr, vec);                          // 45

        // Search any_of
        vector<int> items = {87, 69};
            // Search any one of the item in items
        itr = find_first_of(vec.begin(), vec.end(), items.begin(), items.end());
        printVectorIterator(itr, vec);                          // 87
            // Search any one of the item in the items that satisfy: x == 4*y
        itr = find_first_of(vec.begin(), vec.end(), items.begin(), items.end(),
                        [](int x, int y){return x == 4*y;});
        printVectorIterator(itr, vec);                          // 348

        // Search Adjacent
            // find two adjacent items that are the same
        itr = adjacent_find(vec.begin(), vec.end());
        printVectorIterator(itr, vec);                          // 69
            // find two adjacent items that satisfy: x == 4*y
        itr = adjacent_find(vec.begin(), vec.end(), [](int x, int y){return x == 4*y;});
        printVectorIterator(itr, vec);                          // No such pair found.
    }

    {
        // 4. Comparing Ranges
        vector<int> vec = {9, 60, 90, 8, 45, 45, 87, 90, 69, 69, 55, 7, 348, 276, 276};

        vector<int> vec2 = {9, 60, 90, 8, 45, 45, 87, 90, 69, 69, 55, 7, 348, 276, 276};
        if (equal(vec.begin(), vec.end(), vec2.begin())) {
            cout << "vec and vec2 are the same.\n";
        }

        vector<int> vec3 = {9, 60, 90, 8, 69, 69, 55, 7, 348, 45, 45, 87, 90, 276, 276};
        if (is_permutation(vec.begin(), vec.end(), vec3.begin()) && !equal(vec.begin(), vec.end(), vec3.begin())) {
            cout << "vec and vec3 have same items, but in different order.\n";
        }

        // find first difference
        // pair_of_itr.first is and iterator of vec
        // pair_of_itr.second is an iterator of vec4
        vector<int> vec4 = {9, 60, 90, 8, 45, 87, 90};
        auto pair_of_itr = mismatch(vec.begin(), vec.end(), vec4.begin());
        printVectorIterator(pair_of_itr.first, vec);            // 45
        printVectorIterator(pair_of_itr.second, vec4);          // 87

        // Lexicographical Comparison: one-by-one comparison with "less than"
        vector<int> vec5 = {9, 60, 90, 60, 90, 8, 45, 8, 45, 87, 90};
        bool less_than = lexicographical_compare(vec.begin(), vec.end(), vec5.begin(), vec5.end());
        if (less_than) {
            cout << "vec is less than vec5.\n";                 // <-
        } else {
            cout << "vec is NOT less than vec5.\n";
        }
        // {1, 2, 3, 5} < {1, 2, 4, 5}
        // {1, 2}       < {1, 2, 3}

        // Generalized forms:
        //   equal(), is_permutation(), mismatch(), lexicographical_compare()
    }

    {
        // 5. Check Attributes
        vector<int> vec = {9, 60, 90, 8, 45, 45, 87, 90, 69, 69, 55, 7, 348, 276, 276};

        bool vec_is_soted = is_sorted(vec.begin(), vec.end());  // Check if vec is sorted
        if (vec_is_soted) {
            cout << "vec is sorted.\n";
        } else {
            cout << "vec is NOT sorted.\n";                     // <-
        }

        // itr points to first place to where elements are no longer sorted
        auto itr = is_sorted_until(vec.begin(), vec.end());
        printVectorIterator(itr, vec);                          // 8

        // Generalized forms:
        //   is_sorted(), is_sorted_until()

        // Check if vec is partitioned in two (and only two) according to the condition of (x > 80)
        bool vec_is_partitioned = is_partitioned(vec.begin(), vec.end(), [](int x){return x > 80;});
        if (vec_is_partitioned) {
            cout << "vec is partitioned.\n";
        } else {
            cout << "vec is NOT partitioned.\n";                // <-
        }

        // Check if vec is a heap
            // A heap is a specific type of binary tree-based data structure where the value of a parent node
            //     is either greater than or equal to (max-heap) or less than or equal to (min-heap) the values
            //     of its children nodes.
            // In a vector, a heap can be represented where each parent node's value is greater than or equal to
            //     its children's values. This is called a max-heap.
        bool vec_is_heap = is_heap(vec.begin(), vec.end());
        if (vec_is_heap) {
            cout << "vec is heap.\n";
        } else {
            cout << "vec is NOT heap.\n";                       // <-
        }

        // Example vector that is a max-heap
            // A max heap is a data structure in which each child node is less than or equal to its parent node.
            // A min heap is a similar type of data structure where each child node is greater than or equal to its parent node.
            // Thus, heapifying a heap tree means reordering the child nodes so that they conform to either
            //     min heap or max heap rules.
        std::vector<int> vec2 = {100, 90, 80, 70, 60, 60, 50, 40, 40, 30, 20, 10};
        vec_is_heap = is_heap(vec2.begin(), vec2.end());
        if (vec_is_heap) {
            cout << "vec is heap.\n";                           // <-
        } else {
            cout << "vec is NOT heap.\n";
        }

        // find the first place where it is no longer a heap (binary tree)
            //                   9 (index 0)
            //                 /   \
            //             60 (1)    90 (2)
            //             /  \      /  \
            //          8(3) 45(4) 45(5) 87(6)
            //          / \    / \   / \
            //       90(7)69(8)69(9)55(10)
            //       /  \
            //    7(11) 348(12)

        itr = is_heap_until(vec.begin(), vec.end());
        printVectorIterator(itr, vec);                          // 60
        // Generalized formas: is_heap(), is_heap_until()

        // All, any, none
            // If all of vec is bigger than 80
        bool vec_all_of = all_of(vec.begin(), vec.end(), [](int x){return x > 80;});
        if (vec_all_of) {
            cout << "vec is entirely greater than 80.\n";
        } else {
            cout << "vec is NOT entirely greater than 80.\n";   // <-
        }

            // If any of vec is bigger than 80
        bool vec_any_of = any_of(vec.begin(), vec.end(), [](int x){return x > 80;});
        if (vec_any_of) {
            cout << "vec has at least one element greater than 80.\n";   // <-
        } else {
            cout << "vec has NOT at least one element greater than 80.\n";
        }

            // If none of vec is bigger than 80
        bool vec_none_of = none_of(vec.begin(), vec.end(), [](int x){return x > 80;});
        if (vec_none_of) {
            cout << "vec has none element greater than 80.\n";
        } else {
            cout << "vec has at least one element greater than 80.\n";   // <-
        }

    }

    return 0;
}
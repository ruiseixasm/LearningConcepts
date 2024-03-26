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
     * Sorting in STL
     */
    // Sorting algorith requires random access iterator:
    //    vector, deque, container array, native array
    {
        vector<int> vec = {9, 1, 10, 2, 45, 3, 90, 4, 9, 5, 8};

        // sort with the default operator <
        sort(vec.begin(), vec.end());
        printContainer(vec);            // 1 2 3 4 5 8 9 9 10 45 90

        vec = {9, 1, 10, 2, 45, 3, 90, 4, 9, 5, 8};

        // sort with lambda function
        sort(vec.begin(), vec.end(), [](int x, int y){return x%10 < y%10;});
        printContainer(vec);            // 10 90 1 2 3 4 45 5 8 9 9
    }

    // Sometimes we don't need complete sorting.
    // Problem #1: Finding top 5 students accordingly to their teest scores.
    //  - partial sort
    std::cout << std::endl;
    {
        vector<int> vec = {9, 60, 70, 8, 45, 87, 90, 69, 69, 55, 7};

        partial_sort(vec.begin(), vec.begin() + 5, vec.end(), greater<int>());
        printContainer(vec);            // 90 87 70 69 69 8 9 45 60 55 7

        // Alternatives for greater<int>()     (>):
        //     1. less<int>()                  (<)      (default)
        //     2. greater_equal<int>()         (>=)
        //     3. less_equal<int>()            (<=)
        //     4. lambda function
        //     5. functor

        vec = {9, 60, 70, 8, 45, 87, 90, 69, 69, 55, 7};

        // Overloaded:
        partial_sort(vec.begin(), vec.begin() + 5, vec.end());
        printContainer(vec);            // 7 8 9 45 55 87 90 70 69 69 60
    }

    // Problem #2: Finding top 5 students accordingly to their scope,
    //     but I don't care their order.
    std::cout << std::endl;
    {
        vector<int> vec = {9, 60, 70, 8, 45, 87, 90, 69, 69, 55, 7};

        nth_element(vec.begin(), vec.begin() + 5, vec.end(), greater<int>());
        printContainer(vec);            // 69 87 70 90 69 60 45 8 9 55 7
    }

    // Problem #3: Move the students whose score is less than 10 to the front.
    std::cout << std::endl;
    {
        vector<int> vec = {9, 60, 70, 8, 45, 87, 90, 69, 69, 55, 7};

        partition(vec.begin(), vec.end(), [](int i){return i < 10;});
        printContainer(vec);            // 9 7 8 70 45 87 90 69 69 55 60

        vec = {9, 60, 70, 8, 45, 87, 90, 69, 69, 55, 7};

        // To preserve the original order within each partition:
        stable_partition(vec.begin(), vec.end(), [](int i){return i < 10;});
        printContainer(vec);            // 9 8 7 60 70 45 87 90 69 69 55
    }

    // Heap Algorithms  (Binary tree)
    //
    // Heap:
    // 1. First element is always the largest
    // 2. Add/remove takes O(log(n)) time
    std::cout << std::endl;
    {
        vector<int> vec = {9, 1, 10, 2, 45, 3, 90, 4, 9, 5, 8};

        make_heap(vec.begin(), vec.end());  // descendants are always smaller
        printContainer(vec);                // 90 45 10 9 8 3 9 4 2 5 1
        //                  90
        //             /          \
        //            45           10
        //          /    \        /   \
        //         9      8      3     9
        //        /  \    / \
        //      4    2   5   1

        // Remove the largest element:
        pop_heap(vec.begin(), vec.end());   // 1. Swap vec[0] with last item vec[size - 1]
                                            // 2. Heapify [vec.begin(), vec.end() - 1)
        printContainer(vec);                // 45 9 10 4 8 3 9 1 2 5 90

        vec.pop_back();                     // Remove the last item (the largest one)
        printContainer(vec);                // 45 9 10 4 8 3 9 1 2 5

        vec.push_back(100);                 // Add a new element
        push_heap(vec.begin(), vec.end());  // Heapify the last item in vec
        printContainer(vec);                // 100 45 10 4 9 3 9 1 2 5 8

        vec = {9, 1, 10, 2, 45, 3, 90, 4, 9, 5, 8};

        make_heap(vec.begin(), vec.end());  // Heapify the vector
        printContainer(vec);                // 90 45 10 9 8 3 9 4 2 5 1
        sort_heap(vec.begin(), vec.end());  // Heap sorting
        // Note: sort_heap can only work on a heap (has to be a heap file first)
        printContainer(vec);                // 1 2 3 4 5 8 9 9 10 45 90
    }

    return 0;
}
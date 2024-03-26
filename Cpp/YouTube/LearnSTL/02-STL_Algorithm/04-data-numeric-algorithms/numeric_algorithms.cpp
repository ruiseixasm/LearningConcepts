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
     * Numeric Algorithms (in <numeric>)
     *   - Accumulate, inner product, partial sum, adjacent difference
     */

    {
        // 1. Accumulate

        vector<int> vec = {8, 9, 9, 9};         // 4 items

        // applies adding (+) for each element and adds 10
        int x = accumulate(vec.begin(), vec.end(), 10);
        cout << "x = " << x << endl;            // x = 45       (10 + 8 + 9 + 9 + 9)

        // applies multiplication (*) for each element and multiplies by 10
        x = accumulate(vec.begin(), vec.end(), 10, multiplies<int>());
        cout << "x = " << x << endl;            // x = 58320    (10 * 8 * 9 * 9 * 9)
    }

    cout << endl;
    {
        // 2. Inner Product

        vector<int> vec = {9, 60, 70, 8, 45, 87, 90};       // 7 items

        int x = inner_product(vec.begin(), vec.begin() + 3, // Range #1
                                vec.end() - 3,              // Range #2
                                10);                        // Init value
                                        //             9   60   70 8 45 87 90
                                        //             *    *    *
                                        // 9 60 70 8  45   87   90
                                        //           405 5220 6300
                                        //       10 +   +    +    = 11935
        cout << "x = " << x << endl;    // x = 11935

        x = inner_product(vec.begin(), vec.begin() + 3,     // Range #1
                                vec.end() - 3,              // Range #2
                                10,                         // Init value
                                multiplies<int>(),
                                plus<int>());                        
                                        //             9   60   70 8 45 87 90
                                        //             +    +    +              (plus<int>())
                                        // 9 60 70 8  45   87   90
                                        //            54  147  160
                                        //       10 *   *    *    = 12700800    (multiplies<int>())
        cout << "x = " << x << endl;    // x = 12700800
    }

    cout << endl;
    {
        // 3. Partial Sum

        vector<int> vec = {9, 60, 70, 8, 45, 87, 90};       // 7 items
        vector<int> vec2(7, 0);                             // 7 zeroes

        partial_sum(vec.begin(), vec.end(), vec2.begin());
                                            // 9  9   9   9   9   9   9
                                            //   60  60  60  60  60  60
                                            //       70  70  70  70  70
                                            //            8   8   8   8
                                            //          (+)
        printContainer(vec2);               // 9 69 139 147 192 279 369

        partial_sum(vec.begin(), vec.end(), vec2.begin(), multiplies<int>());
                                            // 9  9   9   9   9   9   9
                                            //   60  60  60  60  60  60
                                            //       70  70  70  70  70
                                            //            8   8   8   8
                                            //          (*)                     (multiplies<int>())
        printContainer(vec2);               // 9 540 37800 302400 13608000 1183896000 -823542400

        adjacent_difference(vec.begin(), vec.end(), vec2.begin());
                                            // (vec[i + 1] - vec[i])
                                            // 9  9
                                            //   60 60
                                            //      70  70
                                            //           8  8
                                            //          (-)
        printContainer(vec2);               // 9 51 10 -62 37 42 3

        adjacent_difference(vec.begin(), vec.end(), vec2.begin(), plus<int>());
                                            // (vec[i + 1] + vec[i])
                                            // 9  9
                                            //   60  60
                                            //       70 70
                                            //           8  8
                                            //          (+)                     (plus<int>())
        printContainer(vec2);               // 9 69 130 78 53 132 177
    }

    return 0;
}
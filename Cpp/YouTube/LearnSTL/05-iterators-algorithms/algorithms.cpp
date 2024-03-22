#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

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
    }

    // Iterate over the set using a range-based for loop
    for (const T& element : container) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main() {

    /*
     * Algorithms
     *   - mostly loops
     */
    vector<int> vec = {4, 2, 5, 1, 9, 3};
    vector<int>::iterator itr = min_element(vec.begin(), vec.end());    // itr -> 1

    // Note 1: Algorithm always process ranges in a half-open way:  [begin, end)
    sort(vec.begin(), itr);     // vec: {2, 4, 5, 1, 9, 3}
    printContainer(vec);
    reverse(itr, vec.end());    // vec: {2, 4, 5, 9, 3, 1}  itr -> 9
    printContainer(vec);

    // Note 2:
    vector<int> vec2(3);
    copy(itr, vec.end(),    // Source
            vec2.begin());  // Destination
            // vec2 needs to have at least space for 3 elements
    printContainer(vec2);

    // Note 3:
    vector<int> vec3;
    copy(itr, vec.end(), back_inserter(vec3));  // Inserting instead of overwriting
                                                // back_insert_iterator is NOT efficient
    printContainer(vec3);
    vec3.insert(vec3.end(), itr, vec.end());    // Efficient and safe
    printContainer(vec3);

    // Note 4: Algorithm with function
    auto isOdd = [](int i) -> bool {    // Lambda function
        return i%2 != 0;
    };

    vector<int> vec4 = {2, 4, 5, 9, 2};
    vector<int>::const_iterator citr = find_if(vec4.begin(), vec4.end(), isOdd);
    cout << "Iterator element: " << *citr << endl;

    // Note 5: Algorithm works with native C++ array too
    int arr[4] = {6, 3, 7, 4};
    sort(arr, arr + 4);     // Because a pointer can be thinked as an iterator
    cout << "Array: " << *arr << endl;  // same as arr[0], = 3, sorted

    return 0;
}
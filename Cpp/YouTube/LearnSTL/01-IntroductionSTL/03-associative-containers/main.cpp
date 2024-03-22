#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <list>
#include <set>
#include <utility> // Include the <utility> header for std::pair
#include <map>

using namespace std;

template<typename T>
void printSet(const std::set<T>& inputSet) {
    std::cout << "Contents of the set:" << " ";
    // Iterate over the set using a range-based for loop
    for (const T& element : inputSet) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void printMultiset(const std::multiset<T>& inputSet) {
    std::cout << "Contents of the multiset:" << " ";
    // Iterate over the multiset using a range-based for loop
    for (const T& element : inputSet) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

template<typename SetType>
void printSetType(const SetType& inputSet) {
    // Deduce the value type of the container
    using T = typename SetType::value_type;

    // Determine the container type and print appropriate message
    if constexpr (std::is_same_v<SetType, std::set<T>>) { // constexpr forces evaluation at compile time
        std::cout << "Contents of the set:" << " ";
    } else if constexpr (std::is_same_v<SetType, std::multiset<T>>) {
        std::cout << "Contents of the multiset:" << " ";
    }

    // Iterate over the set using a range-based for loop
    for (const T& element : inputSet) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

/*
 *  Associative Container
 *  Always sorted, default criteria is <
 *  No push_back(), push_front()
 */

int main() {

    /* Properties of set/multiset:
     * 1. Fast search: O(log(n))
     * 2. Traversing is slow (compared to vector & deque)
     * 3. No random access, no [] operator
     * 4. Elements are read-only
     */

    {
        /*
        *  set
        *  - No duplicates
        */
        set<int> myset;
        myset.insert(3);        // myset: {3}
        myset.insert(1);        // myset: {1, 3}
        myset.insert(7);        // myset: {1, 3, 7},    O(log(n)) (fast)

        set<int>::iterator it;
        it = myset.find(7);     // O(log(n)), it points to 7 (fast)
                                // Sequence containers don't even have find() member function
        pair<set<int>::iterator, bool> ret; // pair with iterator (first) and boolean (second)
        // template <class T1, class T2>
        // struct pair {
        //     T1 first;   // Holds the first value of the pair
        //     T2 second;  // Holds the second value of the pair
        // };

        printSet<int>(myset);
        ret = myset.insert(3);  // No new element inserted because it already exists in myset
        printSet(myset);

        // If the value '3' already exists in the set 'myset', then no new element will be inserted into the set.
        //     Instead, the iterator returned in 'ret.first' will point to the existing element with the value '3',
        //     and 'ret.second' will be 'false', indicating that no insertion occurred.
        // In C++, the std::set::insert function returns a std::pair containing only two elements:
        //     the iterator (ret.first) and a boolean indicating whether the insertion took place (ret.second)
        // In the context of a 'std::pair',
        //     'first' and 'second' are member variables that hold the two values stored within the pair.
        std::cout << "Iterator ret.first: " << *ret.first << std::endl;
        if (!ret.second) it = ret.first;    // "it" now points to element 3 and 'second' is false due to no insertion
        myset.insert(it, 9);    // myset: {1, 3, 7, 9}  O(log(n)) => O(1)
                                // it points to 3 as a hint not required
        myset.erase(it);        // myset: {1, 7, 9}, removes it element that is '3'
        myset.erase(7);         // myset: {1, 9}

        printSet(myset);

        /*
        *  multiset
        *  - With duplicates
        */

        // multiset is a set that allows duplicated items
        multiset<int> mymultiset;
        mymultiset.insert(3);        // mymultiset: {3}
        mymultiset.insert(3);        // mymultiset: {3, 3}
        printMultiset(mymultiset);
        printSetType(mymultiset);

        // set/multiset: value of the elements cannot be modified (read only)
        // *it = 10;   // *it is read-only
    }

    /* Properties of map/multimap:
     * 1. keys cannot be modified
     * 2. type of *it:  pair<const char, int>
     * 3. (*it).first = 'd';    // Error
     */

    {
        /*
        *  map
        *  - No duplicated keys
        */
        map<char, int> mymap;
        mymap.insert(pair<char, int>('a', 100));
        mymap.insert(make_pair('z', 200));

        map<char, int>::iterator it = mymap.begin();
        mymap.insert(it, pair<char, int>('b', 300));    // "it" is a hint

        it = mymap.find('z');   // O(log(n))

        // shoing contents:
        for (it = mymap.begin(); it != mymap.end(); ++it)
            cout << (*it).first << " => " << (*it).second << endl;

        /*
        *  multimap
        *  - Allows duplicated keys
        */
        multimap<char, int> mymultimap;
    }

    return 0;
}
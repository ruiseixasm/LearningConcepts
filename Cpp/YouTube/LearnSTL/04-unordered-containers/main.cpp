#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

void foo(const unordered_map<char, string>& m) {
    //m['S'] = "SUNDAY";        // m is not modifiable (read-only)
    //cout << m['S'] << endl;   // The subscrit sees it as write enabled and also gives a compiling error
    auto itr = m.find('S');
    if (itr != m.end()) {
        //cout << *itr << endl; // Compiling error because it's a key pair, first and second
        cout << itr->first << endl;     // key
        cout << itr->second << endl;    // value
    }
}

int main() {

    /*
     * Properties of Unordered Containers:
     * 1. Fastest search/insert at any place: O(1)
     *      Associative Containers takes O(log(n))
     *      vector, deque takes O(n)
     *      list takes O(1) to insert, O(n) to search
     * 2. Unordered set/multiset: element value cannot be changed.
     *    Unordered map/multimap: element key cannot be changed
     */

    // unordered multiset: unordered set that allows duplicated elements
    // unordered map: unordered set of pairs
    // unordered multimap: unordered map that allows duplicated keys

    // hash collision => performance degradation

    {
        /*
        * unordered set
        */
        unordered_set<string> myset = {"red", "green", "blue"};
        unordered_set<string>::const_iterator itr = myset.find("green");    // O(1)
        if (itr != myset.end())     // Important check (if not loop)
            cout << *itr << endl;
        myset.insert("yellow");     // O(1)

        vector<string> vec = {"purple", "pink"};
        myset.insert(vec.begin(), vec.end());

        // Hash table specific APIs:
        cout << "load_factor = " << myset.load_factor() << endl;
        string x = "red";
        cout << x << " is in bucket #" << myset.bucket(x) << endl;
        cout << "Total bucket #" << myset.bucket_count() << endl;
    }

    {
        /*
         * Associative Array
         * - map and unordered map
         * 1. Search time: unordered_map, O(1); map, O(log(n));
         * 2. unordered_map may degrade to O(n);
         * 3. Can't use multimap and unordered_map, they don't have [] operator.
         */
        unordered_map<char, string> day = {{'S', "Sunday"}, {'M', "Monday"}};
        
        cout << day['S'] << endl;       // No range check
        cout << day.at('S') << endl;    // Has range check

        vector<int> vec = {1, 2, 3};
        vec[5] = 5;                     // Memory leak! Compile Error
        cout << vec.size() << endl;

        day['W'] = "Wednsesday";        // Inserting {'W', "Wednsday"}
        day.insert(make_pair('F', "Friday"));   // Insering {'F', "Friday"}

        day.insert(make_pair('M', "MONDAY"));   // Fails to modify, it's and unordered_map
        day['M'] = "MONDAY";                    // Succeeds to modify

        foo(day);
    }

    {
        /*
         * Container Adaptor
         *  - Provide a restricted interface to meet special needs
         *  - Implemented with fundamental container classes
         * 
         *  1. stack:   LIFO, push(), pop(), top()
         *  2. queue:   FIFO, push(), pop(), front(), back()
         *  3. priority queue:  first item always has the greatest priority
         *                    push(), pop(), top()
         */
    }

    {
        /*
         * Another way of categorizing containers:
         * 1. Array based containers: vector, deque
         * 2. Node base containers: list + associative containers + unordered containers
         * 
         * Array based containers (1.) invalidade pointers:
         *      - Native pointers, iterators, references
         */

        vector<int> vec = {1, 2, 3, 4};
        int* p = &vec[2];       // p points to 3
        vec.insert(vec.begin(), 0);
        cout << *p << endl;     // 2, or ? (memory leak) (undefined behavior)
    }

    return 0;
}

// The main difference between std::map and std::unordered_map lies in their underlying data structures
//     and their performance characteristics:

//     Data Structure:
//         std::map: It is implemented as a self-balancing binary search tree (usually a red-black tree).
//             This structure ensures that the elements are sorted by their keys.
//         std::unordered_map: It is implemented as a hash table, where the elements are not sorted
//             but stored based on their hash values.

//     Ordering:
//         std::map: Elements are ordered by their keys according to the strict weak ordering criterion
//             defined by the comparison function.
//         std::unordered_map: Elements are not ordered. They are organized based on their hash values,
//             so the order of elements is not guaranteed.

//     Performance:
//         std::map: Typically, operations like insertion, deletion, and search have a time complexity
//             of O(log n), where n is the number of elements in the map.
//         std::unordered_map: In general, insertion, deletion, and search operations have an average-case
//             time complexity of O(1). However, in the worst case, they can be O(n), where n is the number
//             of elements in the map.

//     Use Cases:
//         std::map: It's suitable when you need to maintain the order of elements by their keys or when
//             you have a relatively small number of elements, and you need the operations to be consistent
//             in their performance.
//         std::unordered_map: It's preferable when the order of elements doesn't matter, and you prioritize
//             fast insertion, deletion, and search operations, especially for a large number of elements.

// In summary, if you need ordered storage with logarithmic complexity for insertion, deletion, and search,
//     you might prefer std::map. On the other hand, if you prioritize constant-time complexity for these
//     operations and don't need ordered storage, std::unordered_map might be a better choice.
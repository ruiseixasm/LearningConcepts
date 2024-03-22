#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <list>
#include <set>

using namespace std;

int main() {
    vector<int> vec;
    vec.push_back(4);
    vec.push_back(1);
    vec.push_back(8);
    
    // Range crash vs range error
    cout << vec[2] << " ";         // 8    (no range check)
    cout << vec.at(2) << endl;     // 8    (throw range_error exception of out of range)

    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
        cout << vec.at(i) << " ";
    }
    cout << endl;

    for (vector<int>::iterator itr = vec.begin(); itr != vec.end(); itr++)
        cout << *itr << " ";

    cout << endl;

    for (auto it : vec)     // C++ 11
        cout << it << " ";

    cout << endl;

    // Vector is a dynamically allocated continuous array in memory
    int* p = &vec[0];
    p[2] = 6;
    for (auto it : vec)     // C++ 11
        cout << it << " ";
    cout << endl;

    // Common number functions of all containers.
    // vec: {4, 1, 6}
    if (vec.empty()) { cout << "Not possible.\n"; }

    cout << vec.size() << endl;     // 3
    vector<int> vec2(vec);  // Copy constructor, vec2: {4, 1, 6}
    vec.clear();            // Remove all items in vec; vec.size() == 0
    vec2.swap(vec);         // vec2 becomes empty, and vec has 3 items.

    // Notes: No penalty of abstraction, very efficient.

    for (auto it : vec)     // C++ 11
        cout << it << " ";
    cout << endl;

    /* Properties of Vector
     * 1. fast insert/remove at the end: O(1)
     * 2. slow insert/remove at the beginning or in the middle: O(n) (linear time)
     * 3. slow search: O(n)
     */


    /* Deque
     * Can grow at the end and also at the beginning
     */
    deque<int> deq = { 4, 6, 7 };
    deq.push_front(2);      // deq: {2, 4, 6, 7}
    deq.push_back(3);       // deq: {2, 4, 6, 7, 3}

    // Deque has similar interface with vector but is NOT a continuous allocated array in memory
    cout << deq[1] << endl; // 4

    /* Properties of Deque
     * 1. fast insert/remove at the beginning and the end: O(1)
     * 2. slow insert/remove in the middle: O(n) (linear time)
     * 3. slow search: O(n)
     */


    /* List
     * -- double linked list
     * is NOT a continuous allocated array in memory
     */
    list<int> mylist = {5, 2, 9};
    mylist.push_back(6);    // mylist:  {5, 2, 9, 6}
    mylist.push_front(4);   // mylist:  {4, 5, 2, 9, 6}

    list<int>::iterator itr = find(mylist.begin(), mylist.end(), 2);    // itr -> 2     (<algorithm>)
    mylist.insert(itr, 8);      // mylist:  {4, 5, 8, 2, 9, 6}
                                // o(1), faster than vector/deque
    itr++;                      // itr -> 9
    itr = mylist.erase(itr);          // mylist:  {4, 8, 5, 2, 6}     o(1)

    /* Properties of List
     * 1. fast insert/remove at any place: O(1)
     * 2. slow search: O(n) (linear time)
     * 3. no random access, no [] operator.
     */

    list<int> mylist1 = {5, 2, 9, 6};
    list<int> mylist2 = {15, 12, 19, 16};
    list<int>::iterator itr_a = find(mylist2.begin(), mylist2.end(), 15);    // itr -> 2     (<algorithm>)
    list<int>::iterator itr_b = find(mylist2.begin(), mylist2.end(), 19);    // itr -> 2     (<algorithm>)
    // Define iterator itr for position in mylist1 where elements from mylist2 will be spliced
    itr = mylist1.begin();
    mylist1.splice(itr, mylist2, itr_a, itr_b);     // o(1)

    // Output the contents of mylist1 after splice
    std::cout << "mylist1 after splice: ";
    for (int elem : mylist1) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    /* Array
     * 
    */
    int a1[3] = {3, 4, 5};
    array<int, 3> a2 = {3, 4, 5};
    a2.begin();
    a2.end();
    a2.size();

    std::cout << "a2 contents:";
    for (auto it = a2.begin(); it != a2.end(); it++) {
        std::cout << " " << *it; // Print the contents of a2
    }
    std::cout << std::endl;

    array<int, 3> b = {13, 14, 15};
    a2.swap(b);

    std::cout << "a2 contents:";
    for (auto it = a2.begin(); it != a2.end(); it++) {
        std::cout << " " << *it; // Print the contents of a2
    }
    std::cout << std::endl;

    return 0;
}
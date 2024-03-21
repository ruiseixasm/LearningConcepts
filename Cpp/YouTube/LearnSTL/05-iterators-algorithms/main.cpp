#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <algorithm>
#include <string>
#include <iterator> // Needed for istream_iterator
#include <sstream>  // Needed for istringstream cin("0.1 0.2 0.3 0.4");
#include <limits>   // Needed for numeric_limits

using namespace std;

int main() {

    /*
        * Iterators
        */
    {
        // 1. Random Access Iterator: vector, deque, array
        vector<int> myvector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};     // Avoids segmetation fault if empty
        vector<int>::iterator itr = myvector.begin();   // iterator provides mutable access to the elements
        itr = itr + 5;  // advance itr by 5
        itr -= 4;       // retrocesses itr by 4
        vector<int>::iterator itr2 = myvector.begin();
        if (itr2 > itr) itr2 = itr;
        ++itr;          // faster than itr++
        --itr;
    }

    {
        // 2. Bidirectional Iterator: list, set/multiset, map/multimap
        list<int> mylist = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};         // Avoids segmetation fault if empty
        list<int>::const_iterator itr = mylist.begin(); // const_iterator provides read-only access to the elements
        ++itr;
        --itr;   
    }

    {
        // 3. Forward Iterator: forward_list
        forward_list<int> mylist = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Avoids segmetation fault if empty
        forward_list<int>::iterator itr = mylist.begin();
        ++itr;
        // Unordered containers provide "at least" forward iterators.
    }

    {
        // 4. Input Iterator: read and process values while iterating forward.
        vector<int> myvector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};     // Avoids segmetation fault if empty
        vector<int>::const_iterator itr = myvector.begin();   // iconst_iterator provides read-only access to the elements
        int x = *itr;   // x == 1
    }

    {
        // 5. Output Iterator: output values while iterating forward.
        vector<int> myvector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};     // Avoids segmetation fault if empty
        vector<int>::iterator itr = myvector.begin();   // iterator provides mutable access to the elements
        *itr = 100;   // First element becomes 100
    }

    {
        // Every container has an iterator and a const_iterator
        set<int>::iterator itr;
        set<int>::const_iterator citr;  // read-only access to container elements

        set<int> myset = {2, 4, 5, 1, 9};   // Set is an unordered container!
        for (citr = myset.begin(); citr != myset.end(); ++citr) {
            cout << *citr << endl;
            //*citr = 3;    // read-only means can't be changed/writed on
        }
        cout << endl;

        // lambda function (inner function)
        auto MyFunction = [](const int& a) -> void {
            cout << a << " ";
        };
        for_each(myset.cbegin(), myset.cend(), MyFunction); // Only in C++ 11
        cout << endl << endl;

        // Iterator Functions:
        set<int>::iterator itr1 = find(myset.begin(), myset.end(), 4);
        set<int>::iterator itr2 = myset.begin();
        advance(itr2, 4);        // Moves itr forward 4 spots.   itr += 4;
        auto itr_distance = distance(itr1, itr2);   // Measures the distance between itr1 and itr2
        cout << itr_distance << endl;
        cout << endl;
    }

    /*
     * Iterator Adaptor (Predefined Iterator)
     *  - A special, more powerful iterator
     * 1. Insert iterator
     * 2. Stream iterator
     * 3. Reverse iterator
     * 4. Move iterator (C++ 11)
     */

    // 1. Insert Iterator:
    {
        vector<int> vec1 = {4, 5};
        vector<int> vec2 = {12, 14, 16, 18};
        vector<int>::iterator it = find(vec2.begin(), vec2.end(), 16);
        insert_iterator<vector<int>> i_itr(vec2, it);
        copy(vec1.begin(), vec1.end(),  // source
                i_itr);                 // destination
        // lambda function (inner function)
        auto MyFunction = [](const int& a) -> void {
            cout << a << " ";
        };
        // vec2: {12, 14, 4, 5, 16, 18}
        for_each(vec2.cbegin(), vec2.cend(), MyFunction); // Only in C++ 11
        cout << endl << endl;
        // Other insert iterators: back_insert_iterator, front_insert_iterator
    }

    // 2. Stream Iterator:
    {
        istringstream str("0.1 0.2 0.3 0.4");   // can be used in place of cin
        vector<string> vec4;
        // Press Ctrl+D to end cin input!!
        copy(istream_iterator<string>(cin), istream_iterator<string>(),
            back_inserter(vec4));   // Copies each cin element into vec4
        copy(vec4.begin(), vec4.end(), ostream_iterator<string>(cout, " "));    // Prints out vec4
        cout << endl;
        
        cin.clear();    // Makes sure the cin input is cleared from any enter
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // Press Ctrl+D to exit!!
        // Make it terse (straight from cin to cout):
        unique_copy(istream_iterator<string>(cin), istream_iterator<string>(),
                    ostream_iterator<string>(cout, "\n"));
        cout << endl;
    }

    return 0;
}
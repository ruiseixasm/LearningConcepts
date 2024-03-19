/*
 * STL Headers
 */
#include <iostream>
#include <vector>
//#include <iterator>   // No need beacause <vector> indirectly includes <iterator>
#include <algorithm>

/*
 * STL: Standard Template Library
 +   -- Data Structures and Algorithms
 */


// First Example:
using namespace std;

int main() {

    vector<int> vec;
    vec.push_back(4);
    vec.push_back(1);
    vec.push_back(8);   // vec: {4, 1, 8}


    vector<int>::iterator itr1 = vec.begin();   // half-open:   [begin, end)
    vector<int>::iterator itr2 = vec.end();

    for (vector<int>::iterator itr = itr1; itr != itr2; itr++)
        cout << *itr << " ";    // Print out:   4 1 8

    sort(itr1, itr2);   // This is an Algorithm from "#include <algorithm>"

    return 0;
}
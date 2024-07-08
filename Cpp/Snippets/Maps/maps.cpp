#include <iostream>
#include <map>
#include <unordered_map>
#include <chrono>

using namespace std;
using namespace std::chrono;


// Use std::map when you need ordered data and can tolerate O(log n) complexity.
// Use std::unordered_map when you need fast access and do not require order, with average O(1) complexity.

int main() {
    const int num_elements = 1000000;
    
    // Measure time for std::map
    map<int, int> orderedMap;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < num_elements; ++i) {
        orderedMap[i] = i;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by std::map: " << duration.count() << " milliseconds" << endl;

    // Measure time for std::unordered_map
    unordered_map<int, int> unorderedMap;
    start = high_resolution_clock::now();
    for (int i = 0; i < num_elements; ++i) {
        unorderedMap[i] = i;
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by std::unordered_map: " << duration.count() << " milliseconds" << endl;

    return 0;
}

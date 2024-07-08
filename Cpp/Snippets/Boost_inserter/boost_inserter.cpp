#include <iostream>
#include <map>
#include <string>


// The insert() function from Boost.Assign is indeed not a typical function in C++.
//     It is a function provided by the Boost.Assign library, which uses advanced
//     template programming to achieve a concise syntax for populating containers.

// To understand how insert() works, let's break down the mechanism used by Boost.Assign.
//     The library utilizes operator overloading and template techniques to enable
//     a chained syntax for inserting multiple elements. Here’s a simplified version to demonstrate the concept.


// Step 1: Define the wrapper class
template <typename MapType>
class MapInserter {
public:
    MapInserter(MapType& map) : map_(map) {}

    MapInserter& operator()(const typename MapType::key_type& key, const typename MapType::mapped_type& value) {
        map_.insert(std::make_pair(key, value));
        return *this;
    }

private:
    MapType& map_;
};

// Step 2: Define the helper function
template <typename MapType>
MapInserter<MapType> insert(MapType& map) {
    return MapInserter<MapType>(map);
}

// Step 3: Use the helper function
int main() {
    std::map<int, std::string> myMap;
    insert(myMap)(1, "one")(2, "two")(3, "three");

    for (const auto& pair : myMap) {
        std::cout << pair.first << " => " << pair.second << std::endl;
    }

    return 0;
}

#include <iostream>
#include <vector>
#include "boost/foreach.hpp"    // Includes all the BOOST macros

int main() {
    std::vector<std::string> names;
    names.push_back("Tom");
    names.push_back("Dick");
    names.push_back("Harry");
    names.push_back("April");
    names.push_back("May");
    names.push_back("June");

    std::cout << std::endl << "Straight:" << std::endl;
    BOOST_FOREACH(std::string Name, names)
        std::cout << Name << std::endl;

    std::cout << std::endl << "Backward:" << std::endl;
    BOOST_REVERSE_FOREACH(std::string Name, names)
        std::cout << Name << std::endl;


    return 0;
}
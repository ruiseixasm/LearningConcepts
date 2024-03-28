#include <iostream>
#include <vector>
 
int main()
{
    std::vector<int> v = {0, 1, 2, 3, 4, 5};
 
    for (int& i : v) // access by const reference
        i++;
 
    for (const auto i : v) // access by value, the type of i is int
        std::cout << i << ' ';
    std::cout << '\n';
 
    for (auto&& i : v) // access by forwarding reference, the type of i is int&
        i++;
 
    for (const auto i : v) // access by value, the type of i is int
        std::cout << i << ' ';
    std::cout << '\n';
 
    const auto& cv = v; // constant reference to v
 
    for (auto&& i : cv) // access by f-d reference, the type of i is const int&
        //i++;    // Doesn't compile, const int&
        continue;

    for (const auto i : v) // access by value, the type of i is int
        std::cout << i << ' ';
    std::cout << '\n';
}

// OUTPUT:
// 1 2 3 4 5 6 
// 2 3 4 5 6 7 
// 2 3 4 5 6 7 
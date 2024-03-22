#include <iostream>
#include <set>
#include <type_traits>

// Define Lsb_less functor
struct Lsb_less {    
    bool operator()(int x, int y) const {
        return x % 10 < y % 10;
    }
};

// Function template foo
template<typename ContainerType, typename T>
void foo(const ContainerType& container) {
    if constexpr (std::is_same_v<ContainerType, std::set<T, Lsb_less>>) {
        std::cout << "It's a set<int, Lsb_less>!" << std::endl;
    } else {
        std::cout << "It's not a set<int, Lsb_less>!" << std::endl;
    }
}

int main() {
    std::set<int, Lsb_less> my_set;
    std::set<int> default_set;

    return 0;
}

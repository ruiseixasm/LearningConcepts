#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>    // for pow function
#include <deque>

using namespace std;

// Forward declaration of Lsb_less
struct Lsb_less;

template<typename ContainerType>
void printContainer(const ContainerType& container) {
    // Deduce the value type of the container
    using T = typename ContainerType::value_type;

    // Determine the container type and print appropriate message
    if constexpr (std::is_same_v<ContainerType, std::set<T>>) { // constexpr forces evaluation at compile time
        std::cout << "Contents of the set:" << " ";
    } else if constexpr (std::is_same_v<ContainerType, std::multiset<T>>) {
        std::cout << "Contents of the multiset:" << " ";
    } else if constexpr (std::is_same_v<ContainerType, std::vector<T>>) {
        std::cout << "Contents of the vector:" << " ";
    } else if constexpr (std::is_same_v<ContainerType, std::deque<T>>) {
        std::cout << "Contents of the deque:" << " ";
    } else if constexpr (std::is_same_v<ContainerType, std::set<T, Lsb_less>>) {
        std::cout << "Contents of a specific set:" << " ";
    }

    // Iterate over the set using a range-based for loop
    for (const T& element : container) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

/*
 * Benefits of functor:
 * 1. Smart function: capabilities beyond operator()
 *    It can remember state.
 * 2. It can have its own type.
 */

/*
 * Function Ojects (functors)
 */
class X1 {
    public:
    void operator()(string str) {   // Defines operator parentheses () for X (type before the operator)
        cout << "Calling functor X1 with parameter " << str << endl;
    }
    // Not to confused with a type conversion function
    operator string () const { return "X1"; }    // type conversion function
};

/*
 * Parameterized Function
 */
class X2 {
    public:
    X2(int i) {}
    void operator()(string str) {   // Defines operator parentheses () for X (type before the operator)
        cout << "Calling functor X2 with parameter " << str << endl;
    }
};

// Regular funtions
void add2(int i) {
    cout << i + 2 << " ";
}

int value = 2;  // Nasty codding practice!
void addValue(int i) {
    cout << i + value << " ";
}

template<int valParameter>  // It has to be a compile time constant!
void addValParameter(int i) {
    cout << i + valParameter << " ";
}

// Best solution with a functor
class AddValue {
    int val;
    public:
    AddValue(int j) : val(j) {} // Constructor sets val
    void operator()(int i) {
        cout << i + val << " ";
    }
};

int main() {

    {
        X1 foo;         // X1 cast behaves like a function
        foo("Hi");      // Calling functor X1 with paramenter Hi

        X2(8)("Hi");

        vector<int> vec = {2, 3, 4, 5};
        for_each(vec.begin(), vec.end(), add2); // {4, 5, 6, 7}
        cout << endl;
        for_each(vec.begin(), vec.end(), addValue); // {4, 5, 6, 7}
        cout << endl;
        for_each(vec.begin(), vec.end(), addValParameter<2>);   // {4, 5, 6, 7}
        cout << endl;

        int value = 3;  // Now it can be a variable to set AddValue to be added to the input i
        for_each(vec.begin(), vec.end(), AddValue(value));      // {5, 6, 7, 8}
        cout << endl;

        // Output both global and local variables
        cout << "Global variable: " << ::value << endl; // Access global variable using the scope resolution operator (::)
        cout << "Local variable: " << value << endl;

        /*
        * Build-in Functors
        */
        // less greater greater_equal less_equal not_equal_to
        // logical_and logical_not logical_or
        // multiplies minus plus divide modulus negate

        int x = multiplies<int>()(3, 4);    // x = 3 * 4
        if (not_equal_to<int>()(x, 10))     // if (x != 10)
            cout << x << endl;
    }

    {
        /*
         * Parameter Binding
         */

        int x = multiplies<int>()(2, 3);    // x = 3 * 4
        // /// One of the @link arithmetic_functors math functors@endlink.
        // template<typename _Tp>
        // struct multiplies : public binary_function<_Tp, _Tp, _Tp>
        // {
        //     _GLIBCXX14_CONSTEXPR
        //     _Tp
        //     operator()(const _Tp& __x, const _Tp& __y) const
        //     { return __x * __y; }
        // };

        // Multiply myset's elements by 10 and save in vec:
        set<int> myset = {2, 3, 4, 5};
        vector<int> vec;
        transform(myset.begin(), myset.end(),   // source
                back_inserter(vec),             // destination
                bind(multiplies<int>(), placeholders::_1, 10)); // functor taking one paramenter
                                                                // instead of two
            // First parameter of multiplies<int>() is substituted with myset's element

        // back_inserter:   the insertion is done by calling the push_back()
        // front_inserter:  the collection mush implement push_front() and vector doesn't have it!

        printContainer(vec);

        auto addVal = [](int i, int val) -> void {
            cout << i + val << " ";
        };

        for_each(vec.begin(), vec.end(), bind(addVal, placeholders::_1, 2));
        cout << endl;
        
    }

    {
        // Convert a regular function to a functor
        auto Pow = [](double x, double y) -> double {
            return pow(x, y);
        };

        set<int> myset = {3, 1, 25, 7, 12};
        deque<int> d;
        auto f = function<double (double, double)>(Pow);    // C++ 11 functor
        transform(myset.begin(), myset.end(),   // source
                back_inserter(d),               // destination
                bind(f, placeholders::_1, 2));  // functor
                // d: {1, 9, 49, 144, 625}
        printContainer(d);

        transform(myset.begin(), myset.end(),       // source
                back_inserter(d),                   // destination
                bind(Pow, placeholders::_1, 2));    // lambda function directly
                // d: {1, 9, 49, 144, 625, 1, 9, 49, 144, 625}
        printContainer(d);
    }

    {
        set<int> myset = {3, 1, 25, 7, 12};
        // when (x > 20) || (x < 5), copy from myset to d

        deque<int> d_bool;
        transform(myset.begin(), myset.end(),    // source
                back_inserter(d_bool),           // destination
                bind(logical_or<bool>(),
                    bind(greater<int>(), placeholders::_1, 20),
                    bind(less<int>(), placeholders::_1, 5)
                )
            );
        printContainer(d_bool);

        deque<int> d_copy;
        copy_if(myset.begin(), myset.end(),     // source
                back_inserter(d_copy),          // destination
                bind(logical_or<bool>(),
                    bind(greater<int>(), placeholders::_1, 20),
                    bind(less<int>(), placeholders::_1, 5)
                )
            );
        printContainer(d_copy);

        deque<int> d_func;
        copy_if(myset.begin(), myset.end(),             // source
                back_inserter(d_func),                  // destination
                [](int x) { return x > 20 || x < 5; }   // lambda function
            );
        printContainer(d_func);
    }

    {
        set<int> myset = {3, 1, 25, 7, 12}; // myset: {1, 3, 7, 12, 25}
        printContainer(myset);
        // same as:
        set<int, less<int>> ordered_set = {3, 1, 25, 7, 12};
        printContainer(ordered_set);

        struct Lsb_less {    // a functor that compares the least significan digit
            bool operator()(int x, int y) const {
                return x%10 < y%10;
            }
        };

        set<int, Lsb_less> less_set = {3, 1, 25, 7, 12}; // myset: {1, 12, 3, 25, 7}
        printContainer(less_set);
    }

    {
        /*
         * Predicate
         * A functor or function that:
         * 1. Returns a boolean
         * 2. Does not modify data
         */
        struct NeedCopy {
            bool operator()(int x) const {
                return x > 20 || x < 5;
            }
        };
        set<int> myset = {3, 1, 25, 7, 12}; // myset: {1, 3, 7, 12, 25}
        deque<int> d;
        copy_if(myset.begin(), myset.end(), // source
                back_inserter(d),           // destination
                NeedCopy()
            );
        printContainer(d);

        // Predicate is used for comparison or condition check
    }

    return 0;
}
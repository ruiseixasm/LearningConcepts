#include <iostream>

// Introduction to templates

// Function template
template <typename T>
T square(T x) {
    return x*x;
}

// Class template
template <typename T>
class BoVector {
    T arr[1000];
    int size;
public:
    BoVector():size(0) {}
    void push(T x) { arr[size] = x; size++; }
    T get(int i) const { return arr[i]; }
    int getSize() const { return size; }
    void print() const { for(int i = 0; i < size; i++) { std::cout << arr[i] << std::endl; } }
};

// Operator overloading
template<typename T>
BoVector<T> operator*(const BoVector<T>& left_bv, const BoVector<T>& right_bv) {
    BoVector<T> bv;
    for (int i = 0; i < left_bv.getSize(); i++) {
        bv.push(left_bv.get(i)*right_bv.get(i));
    }
    return bv;
}


int main() {

    // Function template usage
    std::cout << "Function template" << std::endl;
    std::cout << square(5) << std::endl; // int infered
    std::cout << square<double>(5.5) << std::endl; // explicit double

    // Class template usage
    std::cout << "\nClass template" << std::endl;
    BoVector<int> bv; // Has to be slicit int
    bv.push(2);
    bv.push(5);
    bv.push(8);
    bv.push(9);
    bv.print();

    // Operator overloading usage
    std::cout << "\nOperator overloading" << std::endl;
    bv = square(bv);
    bv.print();

    return 0;
}
#include <iostream>
#include <string>

using namespace std;

struct Dog {
    int age_;
    string name_;
};

ostream& operator<< (ostream& sm, const Dog& d) {
    sm << "My name is " << d.name_ << " and my age is " << d.age_ << endl;
    return sm;
}

istream& operator>> (istream& sm, Dog& d) {
    sm >> d.age_;
    sm >> d.name_;
    return sm;
}

int main() {
    Dog d{2, "Bob"};    // Universal Initialization
    cout << d;

    cin >> d;
    cout << d;

    return 0;
}
#include <iostream>
#include <iomanip>      // std::setw and std::setfill

using namespace std;

ostream& endl(ostream& sm) {
    sm.put('\n');
    sm.flush();
    return sm;
}

// // This overloading doesn't work! (says it has to be a template!)
// // main.cpp:13:8: error: specializing member ‘std::basic_ostream<char>::operator<<’ requires ‘template<>’ syntax
// //    13 | ostream& ostream::operator<<(ostream& (*func)(ostream&)) {
// //       |  
// ostream& ostream::operator<<(ostream& (*func)(ostream&)) {
//     return (*func)(*this);
// }

int main() {

    cout << "Hello" << endl;    // endl: '\n' and flush
    // Object? Built-in data type? function?    It's a function!

    cout << ends;   // '\0'
    cout << flush;
    cin >> ws;      // read and discard white spaces

    cout << setw(8) << left << setfill('_') << 99 << endl;  // 99_____

    cout << hex << showbase << 14;  // 0xe

    return 0;
}
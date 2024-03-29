#include <iostream>

using namespace std;

int main() {

    // Formating
    cout << 34 << endl;     // 34
    cout.setf(ios::oct, ios::basefield);
    cout << 34 << endl;     // 42
    cout.setf(ios::showbase);
    cout << 34 << endl;     // 042
    cout.setf(ios::hex, ios::basefield);
    cout << 34 << endl;     // 0x22

    cout.unsetf(ios::showbase);
    cout << 34 << endl;     // 22

    cout.setf(ios::dec, ios::basefield);

    cout.width(10);
    cout << 26 << endl;     //         26
    cout.setf(ios::left, ios::adjustfield);     // 26

    // Floating point value
    cout.setf(ios::scientific, ios::floatfield);
    cout << 340.1 << endl;  // 3.401000e+02
    cout.setf(ios::fixed, ios::floatfield);
    cout << 340.1 << endl;  // 340.100000
    cout.precision(3);
    cout << 340.1 << endl;  // 340.100

    int i;
    cin.setf(ios::hex, ios::basefield); // input as hexadecinal
    cin >> i;                           // 12
    cout << "i: " << i << endl;         // 18

    ios::fmtflags f = cout.flags();
    cout.flags(ios::oct | ios::showbase);

    return 0;
}
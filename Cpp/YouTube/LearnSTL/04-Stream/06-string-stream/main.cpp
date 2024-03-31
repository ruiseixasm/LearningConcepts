#include <iostream>
#include <sstream>      // std::stringstream

using namespace std;

int main() {

    // String Stream
    stringstream ss;    // Stream without IO operation
    // read/write of string

    ss << 89 << "   Hex: " << hex << 89 << "   Oct: " << oct << 89;
    cout << ss.str() << endl;   // 89 Hex:59   Oct: 131

    int a, b, c;
    string s1;

    ss >> hex >> a; // Formatted input works token by token. spaces, tabs, newlines
        // a == 137
    ss >> s1;       // s1: "Hex:"
    ss >> dec >> b; // b == 59

    ss.ignore(6);

    ss >> oct >> c; // c == 89

    // More explicit and with better type safety, more readable
    ostringstream oss;  // Can only be used to format output
    istringstream iss;  // Can only be used to format input

    oss << "More explicit as being to be used as output string!" << endl;
    cout << oss.str();

    return 0;
}
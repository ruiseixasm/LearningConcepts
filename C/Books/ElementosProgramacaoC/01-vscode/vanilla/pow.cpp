// C++ program to find the value of
// the pow(a, b) iteratively
#include <iostream>
using namespace std;

// Driver Code
int main()
{
    int a, b, pow = 1;

    // Input two numbers
    cout << "Base: ";
    cin >> a;
    cout << "Exponent: ";
    cin >> b;

    // Iterate till b from 1
    for (int i = 1; i <= b; i++) {
        pow = pow * a;
    }

    // Print the value
    cout << "Pow: " << pow << endl;
}

#include <iostream>

using namespace std;

int main()
{
    cout << "Hello\tI am your computer talking." << endl;
    cout << 5 + 10 << endl;
    cout << 5 + 10 / 2 * 3 + 25 << endl;
    // This line produces a warning message.
    cout << 12345678 * 100 / 2 * 3 * 3 << endl;
    cout << 5 + 10 / 2 * (3 + 25) << endl;

    cout << "\\tabc" << endl;
    cout << "Backslash and double quote are \"." << endl;
    return 0;
}

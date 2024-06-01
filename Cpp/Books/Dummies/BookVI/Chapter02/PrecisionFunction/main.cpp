#include <iostream>

using namespace std;

int main() {
  cout.setf(ios_base::showpoint);
  cout.precision(4);

  for (int i=1; i<=10; i++) {
      cout << 1.0 / i << endl;
  }

  cout << "\n" << 2.0 << endl;
  cout << 12.0 << endl;
  cout << 12.5 << endl;
  cout << 123.5 << endl;
  cout << 1234.9 << endl;
  cout << 12348.8 << endl;
  cout << 123411.5 << endl;
  cout << 1234111.5 << endl;

  // Precision with zeros on the right.
  cout << "\n" << 123000 << endl;
  cout << 123000.0 << endl;
  cout << 123.0e3 << endl;

  // Only available C++ 17 and above
  // Use the -fext-numeric-literals switch.
  cout << 0x1E078p0 << endl;
  return 0;
}

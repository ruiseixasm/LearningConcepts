#include <iostream>

using namespace std;

typedef char *PChar;

void MyFunction(PChar &x) {
  x = new char('B');
}

int main() {
  PChar ptr = new char('A');
  PChar copy = ptr;
  MyFunction(ptr);
  cout << "ptr points to " << *ptr << endl;
  cout << "copy points to " << *copy << endl;
}

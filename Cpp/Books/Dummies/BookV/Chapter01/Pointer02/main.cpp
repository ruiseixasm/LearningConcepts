#include <iostream>

using namespace std;

typedef char *PChar;

void AnotherFunction(PChar *x) {
  *x = new char('C');
}

int main()
{
  PChar ptr = new char('A');
  PChar copy = ptr;
  AnotherFunction(&ptr);
  cout << "ptr points to " << *ptr << endl;
  cout << "copy points to " << *copy << endl;
}

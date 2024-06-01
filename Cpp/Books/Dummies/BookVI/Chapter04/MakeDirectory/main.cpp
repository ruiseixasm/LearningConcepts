#include <iostream>
#include <stdio.h>
#include <io.h>

using namespace std;

int main() {
  if (mkdir("../abc") != 0)
    cout << "Directory not created." << endl;
  else
    cout << "Directory created." << endl;

  return 0;
}

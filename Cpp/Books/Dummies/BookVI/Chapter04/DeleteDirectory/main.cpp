#include <iostream>
#include <stdio.h>
#include <io.h>

using namespace std;

int main() {
  if (rmdir("../abc") != 0)
    cout << "Directory not deleted." << endl;
  else
    cout << "Directory deleted." << endl;

  return 0;
}

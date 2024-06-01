#include <iostream>

using namespace std;

extern int MyNumbers[];

int main(int argc, char *argv[]) {
  cout << sizeof(MyNumbers) << endl;
  return 0;
}

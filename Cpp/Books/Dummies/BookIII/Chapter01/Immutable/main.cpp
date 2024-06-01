#include <iostream>

using namespace std;

struct Immutable{
  int val{7};
};

int main() {
  const int *test1 = new int(5);
  *test1 = 10;

  const int test2{6};
  test2 = 11;

  const Immutable test3;
  test3.val = 12;

  cout << *test1 << test2 << test3.val << endl;
}

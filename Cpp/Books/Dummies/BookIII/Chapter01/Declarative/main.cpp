#include <iostream>
#include <array>
#include <numeric>

using namespace std;

int main() {
  array<int, 6> ThisArray = {12, 2, 4, 18, 7, 2};
  cout << "Sum of All Elements: " <<
    accumulate(ThisArray.begin(), ThisArray.end(), 0)
    << endl;
  cout << "Sum of Elements 1 through 4: " <<
    accumulate(&ThisArray[1], &ThisArray[5], 0) << endl;
  return 0;
}

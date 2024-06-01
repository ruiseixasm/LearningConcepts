#include <iostream>
#include <array>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
  array<char, 5> Letters = {'a', 'b', 'c', 'd', 'e'};

  for (entry: Letters)
    cout << entry << endl;

  reverse_copy(Letters.begin(), Letters.end(),
               ostream_iterator<char>(cout, " "));
  return 0;
}

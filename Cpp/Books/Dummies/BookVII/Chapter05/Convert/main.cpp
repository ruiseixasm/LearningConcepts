#include <iostream>
#include "boost/numeric/conversion/converter.hpp"

using namespace std;
using namespace boost;
using namespace boost::numeric;

int main() {
  typedef converter<int, double> Double2Int;
  double MyDouble = 2.1;
  int MyInt = Double2Int::convert(MyDouble);

  cout << "The double value is: " << MyDouble << endl;
  cout << "The int value is: " << MyInt << endl;

  // See what happens with a larger value.
  MyDouble = 3.8;
  MyInt = Double2Int::convert(MyDouble);
  cout << "The double value is: " << MyDouble << endl;
  cout << "The int value is: " << MyInt << endl;

  // Round instead of truncate.
  typedef conversion_traits<int, double> Traits;
  typedef converter<int, double, Traits,
    def_overflow_handler, RoundEven<double> >
    Double2Rounded;
  MyInt = Double2Rounded::convert(MyDouble);
  cout << "The int value is: " << MyInt << endl;
  return 0;
}

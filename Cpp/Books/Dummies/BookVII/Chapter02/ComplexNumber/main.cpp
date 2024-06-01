#include <iostream>
#include <complex>

using namespace std;

complex<long double> operator"" _i(long double Value) {
  return complex<double>(0, Value);
}
int main() {
  complex<double> StdComplex(0, 3.14);
  auto AutoComplex = 3.14_i;
  auto UDLComplex = 3.14i;
  auto NonZeroRealPart = 2.01 + 3.14i;

  cout << StdComplex.real() << "\t"
    << StdComplex.imag() << endl;
  cout << AutoComplex.real() << "\t"
    << AutoComplex.imag() << endl;
  cout << UDLComplex.real() << "\t"
    << UDLComplex.imag() << endl;
  cout << NonZeroRealPart.real() << "\t"
    << NonZeroRealPart.imag() << endl;
  return 0;
}

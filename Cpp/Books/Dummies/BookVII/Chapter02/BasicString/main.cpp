#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

using namespace std;
using namespace abi;

string operator"" _s(const char * str, unsigned len) {
  return string{str, len};
}

char* Demangle(const char* Object) {
  int Status;
  char* RealName;
  RealName = __cxa_demangle(Object, 0, 0, &Status);
  return RealName;
}

int main() {
  basic_string<char> StdString = "A standard string.";
  auto AutoString = "This is an auto string."_s;
  auto UDLString = "This is a UDL string."s;

  cout << StdString << endl <<
    Demangle(typeid(StdString).name()) << endl;
  cout << AutoString << endl <<
    Demangle(typeid(AutoString).name()) << endl;
  cout << UDLString << endl <<
    Demangle(typeid(UDLString).name()) << endl;
  return 0;
}

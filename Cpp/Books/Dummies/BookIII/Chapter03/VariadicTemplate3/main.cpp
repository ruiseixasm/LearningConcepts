#include <iostream>
#include <typeinfo>

using namespace std;

auto constraint = [](int x) {return x > 7;};

template<typename T>
bool ProcessArgs(T arg) {
  cout << "Value is: " << arg << endl;
  return constraint(arg);
}

template<typename T, typename... Args>
bool ProcessArgs(T arg, Args... args) {
  cout << "Value is: " << arg << endl;
  return constraint(arg) && ProcessArgs(args...);
}

int main()
{
  cout << "List contains only numbers above 7: "
    << (ProcessArgs(10, 11, 14, 8) ? "True" : "False")
    << endl << endl;

  cout << "List contains only numbers above 7: "
    << (ProcessArgs(10, 3, 6) ? "True" : "False")
    << endl;;
  return 0;
}

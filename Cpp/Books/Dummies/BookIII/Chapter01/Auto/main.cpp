#include <iostream>
#include <typeinfo>
#include <memory>
#include <cxxabi.h>

using namespace std;

string DemangleIt(const char* Mangled) {
  int Status;
  unique_ptr<char[], void(*)(void*)> Result(
    abi::__cxa_demangle(Mangled, 0, 0, &Status), free);
  return Result.get() ? string(Result.get()) : "Error";
}

void DisplayIt(auto Value) {
  cout << Value << " is of the " <<
    DemangleIt(typeid(Value).name()) << " type." << endl;
}

int main() {
  auto Hello1 = "Hello There!";
  string Hello2 = "Hello Again!";
  auto Number1 = 1234;
  int Number2 = 5678;
  auto Float1 = 12.34;
  float Float2 = 56.78;
  auto Boolean1 = true;
  bool Boolean2 = false;

  DisplayIt(Hello1);
  DisplayIt(Hello2);
  DisplayIt(Number1);
  DisplayIt(Number2);
  DisplayIt(Float1);
  DisplayIt(Float2);
  DisplayIt(Boolean1);
  DisplayIt(Boolean2);

  return 0;
}

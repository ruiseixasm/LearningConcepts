#include <iostream>
#include <experimental/optional>

using namespace std;

void myFunction(experimental::optional<string> name = experimental::nullopt) {
  if (name == experimental::nullopt) {
    cout << "I wish I knew your name!" << endl;
  }
  else {
    cout << "Hello " << name.value() << "!" << endl;
  }
}

int main()
{
  myFunction();
  string name = "Sarah";
  experimental::optional<basic_string<char> > theName(name);
  myFunction(theName);
  return 0;
}

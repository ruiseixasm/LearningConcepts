#include <iostream>
#include <map>

using namespace std;

class StoreMe {
public:
  int Item;
};

bool operator < (const StoreMe & first,
const StoreMe & second) {
  return first.Item < second.Item;
}

int main() {
  // First try storing the instances
  map<StoreMe, StoreMe> instances;
  StoreMe key1 = {10}; // braces notation!
  StoreMe value1 = {20};
  StoreMe key2 = {30};
  StoreMe value2 = {40};
  instances[key1] = value1;
  instances[key2] = value2;

  value1.Item = 12345;
  cout << instances[key1].Item << endl;
  instances[key1].Item = 34567;
  cout << instances[key1].Item << endl;

  // Next try storing pointers to the instances
  map<StoreMe*, StoreMe*> pointers;
  StoreMe key10 = {10};
  StoreMe value10 = {20};
  StoreMe key11 = {30};
  StoreMe value11 = {40};
  pointers[&key10] = &value10;
  pointers[&key11] = &value11;

  value10.Item = 12345;
  cout << (*pointers[&key10]).Item << endl;

  // Finally try storing references to the instances.
  // Commented out because it causes an error.)
  map<StoreMe&, StoreMe&> references;

  // The error in the line map<StoreMe&, StoreMe&> references; arises because the C++ Standard Library containers,
  // such as std::map, require the template parameters (key and value types) to be copyable and assignable,
  // which references are not. Additionally, references themselves cannot be used as template parameters
  // for STL containers because they lack value semantics.


  return 0;
}

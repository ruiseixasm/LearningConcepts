#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

void DumpClass(vector<string> *myvector) {
  vector<string>::iterator iter = myvector->begin();
  while (iter != myvector->end())
  {
    cout << *iter << endl;
    iter++;
  }
}

int main() {
  set<string> English;
  English.insert("Zeus");
  English.insert("Magellan");
  English.insert("Vulcan");
  English.insert("Ulysses");
  English.insert("Columbus");

  set<string> History;
  History.insert("Vulcan");
  History.insert("Ulysses");
  History.insert("Ra");
  History.insert("Odin");

  vector<string> Intersect;
  set_intersection(English.begin(), English.end(),
    History.begin(), History.end(),
    back_inserter(Intersect));  // Only works for vectors or deques (push_back)
  cout << "===Intersection===" << endl;
  DumpClass(&Intersect);

  vector<string> Union;
  set_union(English.begin(), English.end(),
    History.begin(), History.end(),
    back_inserter(Union));    // Only works for vectors or deques (push_back)
  cout << endl << "===Union===" << endl;
  DumpClass(&Union);
  return 0;
}

#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

void DumpClass(set<string> *myset) {
  set<string>::iterator iter = myset->begin();
  while (iter != myset->end())
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

  set<string> Intersect;
  insert_iterator<set<string> >
    IntersectIterate(Intersect, Intersect.begin());
  set_intersection(English.begin(), English.end(),
    History.begin(), History.end(), IntersectIterate);
  cout << "===Intersection===" << endl;
  DumpClass(&Intersect);

  set<string> Union;
  insert_iterator<set<string> >
    UnionIterate(Union, Union.begin());
  set_union(English.begin(), English.end(),
    History.begin(), History.end(), UnionIterate);
  cout << endl << "===Union===" << endl;
  DumpClass(&Union);
  return 0;
}

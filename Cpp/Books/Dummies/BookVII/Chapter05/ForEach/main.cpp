#include <iostream>
#include <vector>
#include "boost/foreach.hpp"

using namespace std;
using namespace boost;

int main() {
  vector<string> names;
  names.push_back("Tom");
  names.push_back("Dick");
  names.push_back("Harry");
  names.push_back("April");
  names.push_back("May");
  names.push_back("June");

  BOOST_FOREACH(string Name, names)
      cout << Name << endl;

  cout << endl << "Backward:" << endl;
  BOOST_REVERSE_FOREACH(string Name, names)
      cout << Name << endl;
  return 0;
}

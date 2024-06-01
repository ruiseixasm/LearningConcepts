#include <iostream>
#include "boost/regex.hpp"

using namespace std;
using namespace boost;

int main() {
  char MyNumber[80];
  cout << "Type a three-digit number: ";
  cin >> MyNumber;

  regex Expression("[0-9][0-9][0-9]");
  cmatch Matches;

  // Perform a matching check.
  if (regex_match(MyNumber, Matches, Expression)) {
    cout << "You typed: " << Matches << endl;
  } else {
    cout << "Not a three-digit number!" << endl;
  }

  // Perform a search check.
  if (regex_search(MyNumber, Matches, Expression)) {
    cout << "Found: " << Matches << endl;
  } else {
    cout << "No three-digit number found!" << endl;
  }
  return 0;
}


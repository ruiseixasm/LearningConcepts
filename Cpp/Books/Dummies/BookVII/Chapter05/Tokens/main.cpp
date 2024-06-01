#include <iostream>
#include "boost/tokenizer.hpp"

using namespace std;
using namespace boost;

int main() {
  string MyString = "This is a test string!";
  tokenizer<> Tokens(MyString);

  // Display each token on screen.
  tokenizer<>::iterator Iterate;
  for (Iterate = Tokens.begin(); Iterate != Tokens.end();
    Iterate++)
    cout << *Iterate << endl;
  return 0;
}

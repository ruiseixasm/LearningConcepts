#include <iostream>
#include "boost/tokenizer.hpp"

using namespace std;
using namespace boost;

int main() {
  string MyString = "This is a test string!";
  tokenizer<> Tokens(MyString);

// tokenizer<> uses the default template parameter which is char_separator<char>,
//     suitable for tokenizing strings by whitespace.
// The default tokenizer template parameters are set up to use boost::char_separator<char>
//     for whitespace separation.
// This works because the tokenizer class template defaults to char_separator<char>
//     if no template parameters are specified.


  // Display each token on screen.
  tokenizer<>::iterator Iterate;
  for (Iterate = Tokens.begin(); Iterate != Tokens.end();
    Iterate++)
    cout << *Iterate << endl;
  return 0;
}
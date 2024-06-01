#include <iostream>
#include <map>

using namespace std;

int main()
{
  auto greater = [](auto x, auto y) { return x > y; };
  map<string, int, decltype(greater)> MyMap1;

  MyMap1.insert(pair<string, int>("D", 12));
  MyMap1.insert(pair<string, int>("B", 4));
  MyMap1.insert(pair<string, int>("C", 8));
  MyMap1.insert(pair<string, int>("A", 1));

  cout << "MyMap1 Content" << endl;
  for (auto element : MyMap1)
    cout << element.first << "\t" << element.second
      << endl;

  map<string, int, decltype(greater)> MyMap2;
  MyMap2 = MyMap1;
  MyMap1.insert(pair<string, int>("E", 23));
  MyMap2.insert(pair<string, int>("F", 35));

  cout << endl << "MyMap2 Content" << endl;
  for (auto element : MyMap2)
    cout << element.first << "\t" << element.second
      << endl;
}

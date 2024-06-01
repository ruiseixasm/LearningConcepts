#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
  vector<string> MyData;
  MyData.push_back("One");
  MyData.push_back("Two");

  ofstream outfile("../MyData.txt");
  for (Element : MyData)
    outfile << Element << endl;
  outfile.close();
  cout << "File Written!" << endl;
  return 0;
}

#include <iostream>
#include <fstream>

using namespace std;

int main() {
  fstream outfile("../MyFile.txt",
                  ios::in | ios::out | ios::trunc);
  outfile << "Hi" << endl;
  outfile.flush();

  string Data;
  outfile.seekg(0, ios::beg);
  outfile >> Data;
  outfile.close();

  cout << "File Written!" << endl;
  cout << Data << endl;
  return 0;
}

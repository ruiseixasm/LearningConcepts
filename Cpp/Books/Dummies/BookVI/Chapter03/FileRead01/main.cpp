#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main() {
  string weight;
  string height;
  string width;
  string depth;

  ifstream MyFile("../Numbers.txt");
  if (!MyFile) {
    cerr << "File couldn't be opened!" << endl;
    cerr << "Error Code: " << strerror(errno) << endl;
    return -1;
  }

  MyFile >> weight;
  MyFile >> height;
  MyFile >> width;
  MyFile >> depth;

  cout << "Weight = " << weight << "\r\n";
  cout << "Height = " << height << "\r\n";
  cout << "Width  = " << width << "\r\n";
  cout << "Depth  = " << depth;

  MyFile.close();
  return 0;
}

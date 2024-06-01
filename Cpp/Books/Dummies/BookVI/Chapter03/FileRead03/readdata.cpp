#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int ReadFile(string filename) {
  ifstream infile(filename);
  if (!infile) {
    cerr << "File couldn't be opened!" << endl;
    cerr << "Error Code: " << strerror(errno) << endl;
    return -1;
  }

  int num;
  cout << "File: " << filename << endl;

  do {
      infile >> num;
      cout << num << endl;
  } while (!infile.eof());

  infile.close();
  return 0;
}

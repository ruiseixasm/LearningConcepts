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

  int count = 0;
  infile >> count;
  cout << "File: " << filename << endl;
  cout << "This file has " << count << " items." << endl;

  int num = 0;
  for (int i=0; i<count; i++) {
    infile >> num;
    cout << num << endl;
  }

  infile.close();
  return 0;
}

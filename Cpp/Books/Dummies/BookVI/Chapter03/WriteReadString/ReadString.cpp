#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int ReadData(string Filename) {
  ifstream DataFile(Filename);
  if (!DataFile) {
    cerr << "File couldn't be opened!" << endl;
    cerr << "Error Code: " << strerror(errno) << endl;
    return -1;
  }

  string Data = "";
  while (getline(DataFile, Data)) {
    cout << Data << endl;
  }

  DataFile.close();
  return 0;
}

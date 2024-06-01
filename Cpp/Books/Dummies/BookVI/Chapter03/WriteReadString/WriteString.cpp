#include <iostream>
#include <fstream>

using namespace std;

void ClearFile(string Filename) {
  ofstream DataFile;
  DataFile.open(Filename, ios_base::trunc);
  DataFile.close();
}

int WriteData(string Filename, string Text) {
  ofstream DataFile(Filename, ios_base::app);

  if (DataFile.is_open()) {
    DataFile << Text << endl;
  } else {
    cerr << "Unable to open file." << endl;
    return -1;
  }

  DataFile.close();
  return 0;
}

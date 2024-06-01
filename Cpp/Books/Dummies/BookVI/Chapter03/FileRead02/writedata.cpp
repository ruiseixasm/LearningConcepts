#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int WriteFile(string filename, int count, int start) {
  ofstream outfile(filename);
  if (!outfile) {
    cerr << "File couldn't be opened!" << endl;
    cerr << "Error Code: " << strerror(errno) << endl;
    return -1;
  }

  outfile << count << endl;

  for (int i=0; i<count; i++) {
    outfile << start + i  << endl;
  }

  outfile.close();
  return 0;
}

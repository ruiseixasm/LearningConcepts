#include <iostream>

using namespace std;

int WriteFile(string filename, int count, int start);
int ReadFile(string filename);

int main() {
  cout << "Writing the files." << endl;
  if (WriteFile("../nums.txt", 5, 100) == -1)
    return -1;
  cout << "Files written successfully." << endl;

  cout << "\nReading the files.\n" << endl;
  if (ReadFile("../nums.txt") == -1)
    return -1;
  cout << "\nFiles read successfully." << endl;

  return 0;
}

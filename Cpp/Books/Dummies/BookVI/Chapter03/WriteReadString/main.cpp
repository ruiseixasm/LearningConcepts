#include <iostream>

using namespace std;

void ClearFile(string Filename);
int WriteData(string Filename, string Text);
int ReadData(string Filename);

int main() {
  string const file = "../strings.txt";

  ClearFile(file);
  cout << "Data file cleared." << endl;

  int Result = WriteData(file, "Some data to write.");
  Result = WriteData(file, "Some more data to write.");
  Result = WriteData(file, "Third time's a charm.");
  if (Result == 0)
    cout << "Data written successfully!\n" << endl;

  if (ReadData(file) == 0)
    cout << "\nData read successfully!" << endl;

  return 0;
}

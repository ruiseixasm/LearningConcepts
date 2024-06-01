#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Box {
  string Name;
  int Height;
  int Width;
  int Depth;
  double Weight;

  friend ostream& operator << (ostream& Out, Box Data);
};

ostream& operator << (ostream& Out, Box Data) {
  Out << Data.Name << ",";
  Out << Data.Height << ",";
  Out << Data.Width << ",";
  Out << Data.Depth << ",";
  Out << Data.Weight << "\n";
  return Out;
}

int main() {
  string const file = "../boxes.txt";

  Box SamBox;
  SamBox.Name = "Sam's Box";
  SamBox.Height = 4;
  SamBox.Width = 5;
  SamBox.Depth = 6;
  SamBox.Weight = 7.8;

  ofstream OutFile(file, ios_base::trunc);
  OutFile << SamBox << endl;
  OutFile.close();

  Box InData;
  int Field = 0;
  string InString;
  stringstream ISS;
  ifstream InFile(file);

  while(getline(InFile, InString, ',')){
    switch (Field) {
    case 0:
      InData.Name = InString;
      break;
    case 1:
      ISS << InString;
      break;
    default:
      ISS << " " << InString;
      break;
    }

    Field++;
  }
  InFile.close();

  ISS >> InData.Height >> InData.Width >> InData.Depth
      >> InData.Weight;

  cout << "Name: " << InData.Name << endl;
  cout << "Height: " << InData.Height << endl;
  cout << "Width: " << InData.Width << endl;
  cout << "Depth: " << InData.Depth << endl;
  cout << "Weight: " << InData.Weight << endl;

  return 0;
}

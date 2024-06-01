#include <iostream>
#include "boost/filesystem.hpp"

using namespace boost::filesystem;
using namespace std;

int main() {
  if (! exists("Test")) {
    create_directory(path("Test"));
    cout << "Created Directory Test" << endl;
  } else
    cout << "Directory Test Exists" << endl;

  if (! exists("Test/Data.txt")) {
    boost::filesystem::ofstream File("Test/Data.txt");
    File << "This is a test!";
    File.close();
    cout << "Created File Data.txt" << endl;
  } else
    cout << "File Data.txt Exists" << endl;

  if (exists("Test/Data.txt")) {
    cout << "Data.txt contains "
         << file_size("Test/Data.txt")
         << " bytes." << endl;
    boost::filesystem::ifstream File("Test/Data.txt");
    string Data;
    while (! File.eof()) {
      File >> Data;
      cout << Data << " ";
    }
    cout << endl;
    File.close();
  } else
    cout << "File Data.txt Doesn't Exist!" << endl;

  if (exists("Test/Data.txt")) {
    remove(path("Test/Data.txt"));
    cout << "Deleted Data.txt" << endl;
  }

  if (exists("Test")) {
    remove(path("Test"));
    cout << "Deleted Test" << endl;
  }

  return 0;
}

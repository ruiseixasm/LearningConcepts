#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int main() {
  fs::path APath("C:/Temp");
  cout << "Exists: " << fs::exists(APath) << endl
       << "Root Name: " << APath.root_name() << endl
       << "Root Path: " << APath.root_path() << endl
       << "Relative Path: " << APath.relative_path() << endl;
  return 0;
}

#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
  if (rename("dog1.txt", "dog2.txt") == 0)
    cout << "Renaming dog1.txt to dog2.txt." << endl;

  if (rename("dog2.txt","dog1.txt") == 0)
    cout << "Renaming dog2.txt to dog1.txt." << endl;

  if (rename("dog1.txt","temp/dog2.txt") == 0)
    cout << "Renaming dog1.txt to temp/dog2.txt." << endl;

  if (rename("temp/dog2.txt","dog1.txt") == 0)
    cout << "Getting back to start with dog1.txt."
      << endl;

  return 0;
}

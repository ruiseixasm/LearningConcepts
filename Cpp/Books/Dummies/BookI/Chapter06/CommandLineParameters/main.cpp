#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{
  for (int index=1; index < argc; index++)
  {
    cout << argv[index] << endl;
  }

  return 0;
}

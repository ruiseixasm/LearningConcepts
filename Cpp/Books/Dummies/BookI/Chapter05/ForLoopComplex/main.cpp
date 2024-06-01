#include <iostream>

using namespace std;

int main()
{
  int x = 0;
  for (int i=0, j=10; i<=5, j<=20;
    i++, j+=2, cout << i+j << endl, x+=i+j)
  {
  }

  return 0;
}

#include <iostream>

using namespace std;

int main()
{
  int NonConstant[5] = { 1, 2, 3, 4, 5 };
  int OtherList[5] = { 10, 11, 12, 13, 14 };
  OtherList = NonConstant;
}

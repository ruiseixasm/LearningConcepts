#include <iostream>
#include <memory>
#include "../PenClass2/Pen.h"

using namespace std;

int main()
{
  unique_ptr<Pen> MyPen;
  MyPen.reset(new Pen());
  MyPen->InkColor = red;
  cout << MyPen->InkColor << endl;
  MyPen.reset();
  return 0;
}

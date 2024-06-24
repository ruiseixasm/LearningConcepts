#include <iostream>

using namespace std;

class Rock {
public:
  int Weight;
};

class Diamond : virtual public Rock {
public:
  void SetDiamondWeight(int newweight) {
    Weight = newweight;
  }

  int GetDiamondWeight() {
    return Weight;
  }
};

int main(int argc, char *argv[])
{
  Diamond diamond1;
  Diamond diamond2;
  Diamond diamond3;
  diamond1.SetDiamondWeight(10);
  diamond2.SetDiamondWeight(20);
  diamond3.SetDiamondWeight(30);

  cout << diamond1.GetDiamondWeight() << endl;
  cout << diamond2.GetDiamondWeight() << endl;
  cout << diamond3.GetDiamondWeight() << endl;
  
  
  return 0;
}

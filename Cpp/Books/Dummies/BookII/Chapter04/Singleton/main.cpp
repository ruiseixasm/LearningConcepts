#include <iostream>

using namespace std;

class Planet {
private:
  static Planet *inst;
  Planet() {}
  ~Planet() {}
public:
  static Planet *GetInstance();
};

Planet *Planet::inst = 0;

Planet *Planet::GetInstance() {
  if (inst == 0)     {
    inst = new Planet();
  }
  return inst;
}

int main() {
  Planet *MyPlanet = Planet::GetInstance();
  cout << "MyPlanet address: " << MyPlanet << endl;

  Planet *MyPlanet2 = Planet::GetInstance();
  cout << "MyPlanet2 address: " << MyPlanet2 << endl;
  return 0;
}

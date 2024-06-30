#include <iostream>
#include <fstream>
#include <map>

using namespace std;

class Microwave {
  friend ostream &operator <<(ostream &out,
                              Microwave &oven);
public:
  int HighVoltageRadiation;
  int RadioactiveFoodCount;
  int LeakLevel;
  string OvenName;

  typedef map<ostream *, bool> FlagMap;
  static FlagMap Flags;
};

Microwave::FlagMap Microwave::Flags;

ostream &operator <<(ostream &out, Microwave &oven) {
  bool full = true;
  Microwave::FlagMap::iterator iter =
    Microwave::Flags.find(&out);

  if (iter != Microwave::Flags.end()) {
    full = iter->second;
  }

  if (full) {
    out << "High Voltage Radiation: ";
    out << oven.HighVoltageRadiation << endl;
    out << "Radioactive Food Count: ";
    out << oven.RadioactiveFoodCount << endl;
    out << "Leak Level: ";
    out << oven.LeakLevel << endl;
    out << "Oven Name: ";
    out << oven.OvenName;
  } else {
    out << oven.HighVoltageRadiation << ",";
    out << oven.RadioactiveFoodCount << ",";
    out << oven.LeakLevel << ",";
    out << oven.OvenName;
  }
  return out;
}

istream &operator >>(istream &in, Microwave &oven) {
  in >> oven.HighVoltageRadiation;
  in >> oven.RadioactiveFoodCount;
  in >> oven.LeakLevel;
  in >> oven.OvenName;
  return in;
}

//struct FullOvenManip {};  // Makes it unique the typedef

void FullOvenInfo(int) {}

typedef void(*FullPtr)(int);

ostream &operator << (ostream &out, FullPtr) {
  Microwave::Flags[&out] = true;
  return out;
}

//struct MinOvenManip {};  // Makes it unique the typedef

void MinOvenInfo(float) {}

typedef void(*MinPtr)(float);

ostream &operator << (ostream &out, MinPtr) {
  Microwave::Flags[&out] = false;
  return out;
}

int main() {
  Microwave myoven;
  myoven.HighVoltageRadiation = 9832;
  myoven.RadioactiveFoodCount = 7624;
  myoven.LeakLevel = 3793;
  myoven.OvenName = "Burnmaster";

  cout << myoven << endl;
  cout << "============" << endl;
  cout << FullOvenInfo << myoven << endl;
  cout << "============" << endl;
  cout << MinOvenInfo << myoven << endl;

  return 0;
}

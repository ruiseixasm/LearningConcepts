#include <iostream>

using namespace std;

class CrackedMusicCD
{
public:
  string FormerName;
  int FormerLength;
  int FormerProductionYear;
};

int main()
{
  CrackedMusicCD *Missing[10];
  int SMissing = sizeof(Missing)/sizeof(*Missing);

  for (int i=0; i < SMissing; i++)
  {
    Missing[i] = 0;
  }
  return 0;
}

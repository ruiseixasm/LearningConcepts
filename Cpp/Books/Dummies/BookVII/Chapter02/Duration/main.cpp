#include <iostream>
#include <chrono>

using namespace std;

chrono::duration<unsigned long long> operator"" _m(
   unsigned long long Value) {
  return chrono::duration<int, ratio<60>>(Value);
}

int main() {
  chrono::duration<int, ratio<60>>StdTime(20);
  auto AutoTime(20_m);
  auto UDLTime(20min);

  cout << chrono::duration_cast<chrono::seconds>(StdTime)
    .count() << endl;
  cout << chrono::duration_cast<chrono::seconds>(AutoTime)
    .count() << endl;
  cout << chrono::duration_cast<chrono::seconds>(UDLTime)
    .count() << endl;
  return 0;
}

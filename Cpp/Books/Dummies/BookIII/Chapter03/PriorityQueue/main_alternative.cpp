// Compile command: g++ -std=c++20 -o main_alternative.out main_alternative.cpp
#include <iostream>
#include <queue>
#include <functional> // Include this header for std::function

using namespace std;

int main()
{

    // Define the lambda comparator
    auto cmp = [](int a, int b) -> bool { return a > b; };

    // Use std::function to wrap the lambda
    std::priority_queue<int, std::vector<int>, std::function<bool(int, int)>> PQ(cmp);

  PQ.push(10);
  PQ.push(5);
  PQ.push(8);
  PQ.push(1);
  PQ.push(11);

  while (!PQ.empty()) {
    cout << PQ.top() << endl;
    PQ.pop();
  }
}

#include <iostream>
#include <stack>
#include <queue>

using namespace std;

void StackDemo() {
  cout << "===Stack Demo===" << endl;
  stack<int, vector<int> > MyStack;
  MyStack.push(5);
  MyStack.push(10);
  MyStack.push(15);

  cout << MyStack.top() << endl;
  MyStack.pop();
  cout << MyStack.top() << endl;
  MyStack.pop();

  MyStack.push(40);
  cout << MyStack.top() << endl;
  MyStack.pop();
}

void QueueDemo() {
  cout << "===Queue Demo===" << endl;
  queue<int> MyQueue;
  MyQueue.push(5);
  MyQueue.push(10);
  MyQueue.push(15);

  cout << MyQueue.front() << endl;
  MyQueue.pop();
  cout << MyQueue.front() << endl;
  MyQueue.pop();

  MyQueue.push(40);
  cout << MyQueue.front() << endl;
  MyQueue.pop();
}

int main() {
  StackDemo();
  QueueDemo();
  return 0;
}

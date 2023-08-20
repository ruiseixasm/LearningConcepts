#include <iostream>

int value = 33;
int* base = &value;
typedef int& reference;

auto returnStrangeReference() -> const reference {
	return *base;
}

int main(int argc, char* argv[]) {
	std::cout << "Reference return value: " << returnStrangeReference() << std::endl;
	return 0;
}
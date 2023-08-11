#include <iostream>
#include "Printable.h"
#include "References.cpp"

int main(int argc, char* argv[]) {
	std::cout << "Hello World!" << std::endl;

	MyReference::main(0);
	return 0;
}
#include <iostream>
#include "IncludedFunction.h"
//#include "DirectInclude.cpp"	// Doesn't work, will define the same function twice.
								// Doesn't make distinction between declaration and definition

int main(int argc, char* argv[]) {
	std::cout << "2 + 2 = " << AddTwoIntegers(2, 2) << std::endl;
	return 0;
}
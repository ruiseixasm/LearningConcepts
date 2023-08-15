// C++ Program to demonstrate
// static_cast
#include "LibraryDeclarations.h"
#include <iostream>

// Driver code
void StaticCast()
{
	float f = 3.5;

	// Original float number
	std::cout << "The Value of f: " << f;

	// Implicit type case
	// float to int
	int a = f;
	std::cout << "\nThe Value of a: " << a;

	// using static_cast for float to int
	int b = static_cast<int>(f);
	std::cout << "\nThe Value of b: " << b;
}
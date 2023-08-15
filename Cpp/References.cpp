#include <iostream>

class MyReference
{
private:
	
public:
	static void getReference(int& refInteger) {
		refInteger = refInteger + 10;
	}

	static const int& returnReference(int& refInteger) {
		int someNumber = refInteger + 100;
		return someNumber;
	}

	static void main(int someNumber) {

		getReference(someNumber);
		std::cout << "refInteger: " << someNumber <<  std::endl;
		std::cout << "returnReference: " << returnReference(someNumber) << std::endl;
	}

private:

};


#include <iostream>

int main(int argc, char* argv[]) {


	// Create a structure variable called myStructure
	struct {
		int myNum;
		std::string myString;
	} myStructure; // unnamed structure (anonymous)

	// Assign values to members of myStructure
	myStructure.myNum = 1;
	myStructure.myString = "Hello World!";

	// Print members of myStructure
	std::cout << myStructure.myNum << "\n";
	std::cout << myStructure.myString << "\n\n\n";

	//////////////////////////////////////////////////////////////////////////////////////////////////

	struct {
		std::string brand;
		std::string model;
		int year;
	} myCar1, myCar2; // We can add variables by separating them with a comma here

	// Put data into the first structure
	myCar1.brand = "BMW";
	myCar1.model = "X5";
	myCar1.year = 1999;

	// Put data into the second structure
	myCar2.brand = "Ford";
	myCar2.model = "Mustang";
	myCar2.year = 1969;

	// Print the structure members
	std::cout << myCar1.brand << " " << myCar1.model << " " << myCar1.year << "\n";
	std::cout << myCar2.brand << " " << myCar2.model << " " << myCar2.year << "\n\n\n";

	//////////////////////////////////////////////////////////////////////////////////////////////////

	// NEEDED ONLY FOR C NOT C++

	typedef struct myDataType { // This structure is named "myDataType"
		int myNum;
		std::string myString;
	} myDataAlias;

	myDataAlias myVar;

	myVar.myNum = 111;
	myVar.myString = "Only for C";

	std::cout << myVar.myNum << "\n";
	std::cout << myVar.myString << "\n\n\n";

	//////////////////////////////////////////////////////////////////////////////////////////////////

	struct car {
		std::string brand;
		std::string model;
		int year;
	};

	// Create a car structure and store it in myCar1;
	car newCar1;
	newCar1.brand = "BMW";
	newCar1.model = "X5";
	newCar1.year = 1999;

	// Create another car structure and store it in myCar2;
	car newCar2;
	newCar2.brand = "Ford";
	newCar2.model = "Mustang";
	newCar2.year = 1969;

	// Print the structure members
	std::cout << newCar1.brand << " " << newCar1.model << " " << newCar1.year << "\n";
	std::cout << newCar2.brand << " " << newCar2.model << " " << newCar2.year << "\n";


	return 0;
}
#include <iostream>

class MyArray
{
private:

public:
	static int returnSizeOf(const char* someText) {
		return sizeof(someText);
	}

	static int returnSizeOfByReference(const char* (&someText)) {
		return sizeof(someText);
	}

	static int returnSizeOfByReference2(char (&someText)[12]) {
		return sizeof(someText);
	}

	static void main() {

		const char *myConstText = "Const big chunk of constant text.";
		char myOtherText[] = "Other text.";
		char myCharText[] = {'C', 'a', 'r', 0};
		std::cout << "myConstText sizeof: " << sizeof(myConstText) << std::endl;
		std::cout << "returnSizeOf sizeof: " << returnSizeOf(myConstText) << std::endl;
		std::cout << "returnSizeOfByReference sizeof: " << returnSizeOfByReference(myConstText) << std::endl;
		std::cout << "myOtherText sizeof: " << sizeof(myOtherText) << std::endl;
		std::cout << "returnSizeOf sizeof: " << returnSizeOf(myOtherText) << std::endl;
		std::cout << "returnSizeOfByReference sizeof: " << returnSizeOfByReference2(myOtherText) << std::endl;
	}

	static void StringReferences() {

		const char* myConstantString = "Constant string.";
		char myArrayString[] = "Array string.";

		std::cout << " ********* CONSTANT ********* " << std::endl;
		std::cout << "myConstText sizeof: " << sizeof(myConstantString) << std::endl;
		std::cout << "returnSizeOf sizeof: " << returnSizeOf(myConstantString) << std::endl;
		std::cout << "returnSizeOfByReference sizeof: " << returnSizeOfByReference(myConstantString) << std::endl;

		std::cout << " ********* ARRAY ********* " << std::endl;
		std::cout << "myOtherText sizeof: " << sizeof(myArrayString) << std::endl;
		std::cout << "returnSizeOf sizeof: " << returnSizeOf(myArrayString) << std::endl;
		//std::cout << "returnSizeOfByReference sizeof: " << returnSizeOfByReference(myArrayString) << std::endl;
	}

	static void ForArrayLocal() {
		int int_array[] = { 1,2,3,4,5,6,7,8,9,10 };
		for (auto number : int_array) {
			std::cout << "number: " << number << std::endl;
		}
	}

	static void ForArray(int (&someArray)[10]) {
		for (auto number : someArray) {
			std::cout << "number: " << number << std::endl;
		}
	}

	static void ForArrayRemote() {
		int int_array[] = { 1,2,3,4,5,6,7,8,9,10 };
		ForArray(int_array);
	}

private:

};


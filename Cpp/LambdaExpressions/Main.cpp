#include <iostream>
#include <vector>
#include <algorithm> // count_if()

auto greet = []() {
	std::cout << "Hello World!" << std::endl; // lambda function body
};

// lambda function that takes two integer
//  parameters and displays their sum
auto add = [](int a, int b) {
	std::cout << "Sum = " << a + b << std::endl;
};

auto operation = [](int a, int b, std::string op) -> double {
	if (op == "sum") {
		// returns integer value
		return a + b;
	}
	else {
		// returns double value
		return (a + b) / 2.0;
	}
};

int main(int argc, char* argv[]) {

	// call lambda function
	greet();
	// call the lambda function
	add(100, 78);
	// find the sum of num1 and num2
	auto sum = operation(1, 2, "sum");
	std::cout << "Sum = " << sum << std::endl;

	int num_main = 100;
	// get access to num_main from the enclosing function (Capture by value)
	[num_main]() -> void {
		std::cout << num_main << std::endl;
	}();
	// [=] says all the variables of the enclosing function are captured by value.
	[=]() -> void {
		std::cout << num_main << std::endl;
	}();
	// [&] indicates that all the variables are captured by reference.
	[&]() -> void {
		std::cout << num_main << std::endl;
	}();

	// C++ Lambda Function as Argument in STL Algorithm

	// initialize vector of integers
	std::vector<int> nums = { 1, 2, 3, 4, 5, 8, 10, 12 };

	int even_count = count_if(nums.begin(), nums.end(),
			[](int num) {
				return num % 2 == 0;
			}
		);

	std::cout << "There are " << even_count << " even numbers." << std::endl;


	return 0;
}
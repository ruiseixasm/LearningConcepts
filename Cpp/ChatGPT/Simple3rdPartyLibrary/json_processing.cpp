#include "/home/rui/Libraries3rdParty/json/single_include/nlohmann/json.hpp"
// #include "json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

int main() {
    std::ifstream input("data.json");
    json j;
    input >> j;
    input.close();

    // Accessing values
    std::string name = j["name"];
    int age = j["age"];
    std::string city = j["city"];

    std::cout << "Original JSON data:" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "City: " << city << std::endl;

    // Modify data
    j["age"] = 31;
    j["city"] = "Los Angeles";

    // Write modified data to a new file
    std::ofstream output("modified_data.json");
    output << j.dump(4); // Pretty print with indentation
    output.close();

    std::cout << "\nModified JSON data has been written to modified_data.json" << std::endl;

    return 0;
}
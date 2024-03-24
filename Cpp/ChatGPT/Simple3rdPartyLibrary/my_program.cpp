#include <iostream>
// #include "json.hpp"
#include "/home/rui/Libraries3rdParty/json/single_include/nlohmann/json.hpp"


int main() {
    // Define a JSON string
    std::string json_string = R"({"name": "John", "age": 30, "city": "New York"})";

    // Parse the JSON string
    nlohmann::json json_data = nlohmann::json::parse(json_string);

    // Access JSON object elements
    std::cout << "Name: " << json_data["name"] << std::endl;
    std::cout << "Age: " << json_data["age"] << std::endl;
    std::cout << "City: " << json_data["city"] << std::endl;

    return 0;
}

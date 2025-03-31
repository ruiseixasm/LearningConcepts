
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <list>
#include <algorithm>
#include <cmath>                // For std::round
#include <cstdlib>
// Include the JSON library
#include "single_include/nlohmann/json.hpp"

#include <sstream>
#include <fstream>



double get_float(int numerator_number, int denominator_number) {

    double float_number = numerator_number * 60000.0 / denominator_number;
    // Round to three decimal places
    return std::round(float_number * 1000.0) / 1000.0;
}


int main() {

    int numerator_number = 10;
    int denominator_number = 123456;
    std::vector<double> floats_list_100_cpp;
    std::vector<double> floats_list_100_json;

    for (int n = 0; n < 100; ++n) {
        floats_list_100_cpp.push_back(
            get_float(n * numerator_number, denominator_number)
        );
    }

    std::stringstream json_files_buffer;

    const char* filename = "list_of_floats_3.json";
    std::ifstream json_file(filename);
    if (!json_file.is_open()) {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return 1;
    }
    json_files_buffer << json_file.rdbuf();
    json_file.close();
        
    std::string json_files_list = json_files_buffer.str();
    nlohmann::json json_files_data = nlohmann::json::parse(json_files_list.c_str());

    for (nlohmann::json jsonFloat : json_files_data) {

        double json_float = jsonFloat;
        floats_list_100_json.push_back( json_float );
    }


    for (int i = 0; i < 100; ++i) {

        bool equal_floats = floats_list_100_json[i] == floats_list_100_cpp[i];
        std::cout << "float Json: " << floats_list_100_json[i];
        std::cout << "\t\tfloat Cpp: " << floats_list_100_cpp[i];
        std::cout << "\t\tequal floats: " << equal_floats << std::endl;
    }

    return 0;
}



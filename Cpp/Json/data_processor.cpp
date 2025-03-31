
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
        std::cout << "Extracted float: " << json_float << std::endl;

    }

    return 0;
}



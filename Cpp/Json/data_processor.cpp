
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



double get_float(int numerator_number, int denominator_number) {

    double float_number = numerator_number * 60000.0 / denominator_number;
    // Round to three decimal places
    return std::round(float_number * 1000.0) / 1000.0;
}


int main() {

    int numerator_number = 10;
    int denominator_number = 123456;

    
    nlohmann::json json_files_data = nlohmann::json::parse("list_of_floats_3.json");

    for (nlohmann::json jsonFloat : json_files_data) {

        double json_float = jsonFloat;
        std::cout << "Extracted float :" << json_float << std::endl;

    }

    return 0;
}



//
// Created by mmich on 23.03.2022.
//

#ifndef PERCEPTRON_UTILS_H
#define PERCEPTRON_UTILS_H

#include <vector>
#include "Sample.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <set>

namespace utility {


    void preety_print(std::vector<double> &v);
    std::ifstream open_file_to_read(const std::string &path_to_file);
    std::vector<std::vector<std::string>> load_data_set(const std::string &filename);
}

#endif //PERCEPTRON_UTILS_H

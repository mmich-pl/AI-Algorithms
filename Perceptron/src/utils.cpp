//
// Created by mmich on 23.03.2022.
//

#include "../include/utils.h"


void utility::preety_print(std::vector<double> &v) {
    std::cout << "(";
    for (int i = 0; i < v.size(); ++i) {
        if (i > 0)
            std::cout << ", ";
        printf("%.2f", v[i]);

    }
    std::cout << ")\n";
}

std::ifstream utility::open_file_to_read(const std::string &path_to_file) {
    std::ifstream in(path_to_file);
    try {
        if (!in) throw std::logic_error("Unable to open file, check if file path is correct");
        else return in;
    } catch (std::logic_error &e) {
        std::cerr << e.what() << '\n';
        exit(-1);
    }
}

std::vector<std::vector<std::string>> utility::load_data_set(const std::string &filename) {
    const std::regex comma(",");
    auto file = open_file_to_read(filename);
    std::vector<std::vector<std::string>> rows;
    std::string line{};
    while (file && getline(file, line))
        rows.emplace_back(std::sregex_token_iterator(line.begin(), line.end(), comma, -1),
                          std::sregex_token_iterator());
    return rows;
}



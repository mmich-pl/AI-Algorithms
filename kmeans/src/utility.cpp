//
// Created by mmich on 13.04.2022.
//

#include <fstream>
#include <vector>
#include <iostream>
#include <regex>
#include "../include/utility.h"
#include "../include/point.h"

std::ifstream utility::openFileToRead(const std::string &path_to_file) {
    std::ifstream in(path_to_file);
    try {
        if (!in) throw std::logic_error("Unable to open file, check if file path is correct");
        else return in;
    } catch (std::logic_error &e) {
        std::cerr << e.what() << '\n';
        exit(-1);
    }
}

std::vector<std::vector<std::string>> utility::loadDataSet(const std::string &filename) {
    const std::regex comma(",");
    auto file = openFileToRead(filename);
    std::vector<std::vector<std::string>> point_coordinates;
    std::string line{};
    while (file && getline(file, line))
        point_coordinates.emplace_back(std::sregex_token_iterator(line.begin(), line.end(), comma, -1),
                                       std::sregex_token_iterator());
    return point_coordinates;
}


std::vector<Point> utility::getPoints(std::vector<std::vector<std::string>> &point_coordinates) {
    std::vector<Point> points;
    std::vector<double> temp(point_coordinates[0].size());

    for (const auto &vec: point_coordinates) {
        std::transform(vec.begin(), vec.end(),
                       temp.begin(), [](const std::string &val) { return std::stod(val); });

        points.emplace_back(temp);
    }
    return points;
}
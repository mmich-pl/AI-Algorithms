//
// Created by mmich on 13.04.2022.
//

#ifndef KMEANS_UTILITY_H
#define KMEANS_UTILITY_H

#include "point.h"

namespace utility {

    std::ifstream openFileToRead(const std::string &path_to_file);

    std::vector<std::vector<std::string>> loadDataSet(const std::string &filename);

    std::vector<Point> getPoints(std::vector<std::vector<std::string>> &point_coordinates);
}

#endif //KMEANS_UTILITY_H

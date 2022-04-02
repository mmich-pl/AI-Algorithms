#ifndef KNN_UTILITY_H
#define KNN_UTILITY_H

#include <vector>
#include <string>
#include <map>
#include <regex>
#include <fstream>
#include "kdTree.h"

namespace utility {
    std::map<std::string, int> get_groups(const std::vector<std::vector<std::string>> &training_set);

    std::ifstream open_file_to_read(const std::string &path_to_file);

    std::vector<std::vector<std::string>> load_data_set(const std::string &filename);

    kdTree *create_kd_tree(const std::string &filename);

    std::vector<point> get_points(std::vector<std::vector<std::string>> &point_coordinates);
}
#endif

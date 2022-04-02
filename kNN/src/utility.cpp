#include "../include/utility.h"

std::map<std::string, int> utility::get_groups(const std::vector<std::vector<std::string>> &training_set) {
    std::map<std::string, int> map;
    for (const auto &vec: training_set)
        map.insert(std::make_pair(*(vec.end() - 1), 0));
    return map;
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
    std::vector<std::vector<std::string>> point_coordinates;
    std::string line{};
    while (file && getline(file, line))
        point_coordinates.emplace_back(std::sregex_token_iterator(line.begin(), line.end(), comma, -1),
                                       std::sregex_token_iterator());
    return point_coordinates;
}

kdTree *utility::create_kd_tree(const std::string &filename) {
    auto point_coordinates = load_data_set(filename);
    std::vector<point> points = get_points(point_coordinates);

    auto *t = new kdTree(std::begin(points), std::end(points));
    t->set_groups(get_groups(point_coordinates));
    return t;
}

std::vector<point> utility::get_points(std::vector<std::vector<std::string>> &point_coordinates) {
    std::vector<point> points;
    std::vector<double> temp(point_coordinates[0].size());

    for (const auto &vec: point_coordinates) {
        std::transform(vec.begin(), vec.end() - 1,
                       temp.begin(), [](const std::string &val) { return std::stod(val); });

        points.emplace_back(temp, *(vec.end() - 1));
    }
    return points;
}


#include "../include/point.h"

std::ostream &operator<<(std::ostream &out, const point &pt) {
    out << '(';
    for (int i = 0; i < pt.get_dimension(); ++i) {
        if (i > 0)
            out << ", ";
        out << pt.get_coordinate(i);
    }
    out << ')';
    return out;
}

point::point(const std::vector<double> &cords, std::string name) : _coords(cords), _dimension(cords.size()-1),
                                                                   _group_name(std::move(name)) {}

double point::get_coordinate(std::size_t index) const {
    return _coords[index];
}

double point::get_distance(const point &point) const {
    auto distance = 0.0;
    for (std::size_t i = 0; i < _dimension; i++)
        distance += pow(get_coordinate(i) - point.get_coordinate(i), 2);
    return distance;
}

int point::get_dimension() const {
    return (int) _dimension;
}

std::string point::get_group_name() const {
    return _group_name;
}

point::~point() = default;


#ifndef KNN_POINT_H
#define KNN_POINT_H

#include <utility>
#include <vector>
#include <cmath>
#include <ostream>
#include <iostream>

class point {
private:
    std::vector<double> _coords;
    size_t _dimension;
    std::string _group_name;

public:
    friend std::ostream& operator<<(std::ostream& out, const point& pt);

    explicit point(const std::vector<double>& cords, std::string name="");

    double get_coordinate(std::size_t index) const;

    double get_distance(const point &point) const;

    int get_dimension() const;

    std::string get_group_name() const;

    virtual ~point();
};

#endif

#include "../include/point.h"

double Point::distance( const Point &a,const  Point &b) {
    double dist=0;
    for(int i = 0 ; i< a._coordinates.size() ; i++)
        dist += (a._coordinates[i]-b._coordinates[i])*(a._coordinates[i]-b._coordinates[i]);
    return dist;
}

double Point::distance( const Point &b) const {
    return distance(*this,b);
}

double Point::getNearestClusterDistance() const {
    return _nearest_cluster_distance;
}

void Point::setNearestClusterDistance(double nearestClusterDistance) {
    _nearest_cluster_distance = nearestClusterDistance;
}

int Point::getNearestClusterIndex() const {
    return _nearest_cluster_index;
}

void Point::setNearestClusterIndex(int nearestCluster) {
    _nearest_cluster_index = nearestCluster;
}

const std::vector<double> &Point::getCoordinates() const {
    return _coordinates;
}

bool isEqual(std::vector<double> const &v1, std::vector<double> const &v2)
{
    return (v1.size() == v2.size() &&
            std::equal(v1.begin(), v1.end(), v2.begin()));
}

bool Point::operator!=(const Point &other) const {
    return !isEqual(_coordinates, other._coordinates);
}

std::ostream &operator<<(std::ostream &out, const Point &pt) {
    out << '(';
    for (int i = 0; i < pt._coordinates.size(); ++i) {
        if (i > 0)
            out << ", ";
        out << pt._coordinates[i];
    }
    out << ')';
    return out;
}


Point::~Point()  = default;
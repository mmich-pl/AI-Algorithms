#ifndef KMEANS_POINT_H
#define KMEANS_POINT_H

#include <utility>
#include <vector>
#include <ostream>

class Point{
    private:
    std::vector<double> _coordinates;
    double _nearest_cluster_distance{};
    int _nearest_cluster_index{};
public:
    static double distance( const Point& a, const Point &b);
    double distance( const Point &b) const;

    Point(std::vector<double>& input_data) : _coordinates(input_data){};

    double getNearestClusterDistance() const;

    void setNearestClusterDistance(double nearestClusterDistance);

    int getNearestClusterIndex() const;

    void setNearestClusterIndex(int nearestCluster);

    const std::vector<double> &getCoordinates() const;

    bool operator!=(const Point& a) const;

    friend std::ostream &operator<<(std::ostream &out, const Point &pt);

    virtual ~Point();

};
#endif
#ifndef KMEANS_KMEANS_H
#define KMEANS_KMEANS_H

#include <vector>
#include "point.h"


class Kmeans {
private:
    std::vector<Point> _points, _initial_centroids, _current_centroids, _prev_centroids;
    int _k{};
    int randomIndex();
    void printReport(std::vector<std::vector<Point>> &clusters, int iteration);
    void updateNearestCluster(const std::vector<Point>& _centroids);
    int getNextInitialCentroidIndex();
    void updateCentroids();
    static bool equalCentroids(std::vector<Point> &a, std::vector<Point> &b);
    static int getClosestCentroidIndex(const Point &point, const std::vector<Point> &centroids);
    static double calculateDistanceToCentroid(std::vector<Point> &vector, Point &point);

public:
    Kmeans(std::vector<Point>& input_data);
    ~Kmeans();

    std::vector<std::vector<Point> > RunKMeansPP(int K, std::vector<Point> &centroids);

    };

#endif
#include "../include/kmeans.h"

#include <cassert>
#include <random>
#include <iostream>

void Kmeans::updateNearestCluster(const std::vector<Point> &_centroids) {
    for (Point &point: _points) {
        int idx = getClosestCentroidIndex(point, _centroids);
        point.setNearestClusterIndex(idx);
        point.setNearestClusterDistance(point.distance(_centroids[idx]));
    }
}

void Kmeans::updateCentroids() {
    int dimensions = _points[0].getCoordinates().size();
    std::vector<int> freq(_k, 0);
    std::vector<std::vector<double>> coordinates(_k, std::vector<double>(dimensions, 0));
    std::vector<Point> new_centroids;


    for (auto &_point: _points) {
        ++freq[_point.getNearestClusterIndex()];
        for (int j = 0; j < dimensions; j++)
            coordinates[_point.getNearestClusterIndex()][j] += _point.getCoordinates()[j];
    }

    for (int i = 0; i < _k; ++i) {
        if (freq[i])
            for (int j = 0; j < dimensions; ++j) {
                coordinates[i][j] *= (1.0 / (double) freq[i]);
            }
        new_centroids.emplace_back(coordinates[i]);
    }

    _current_centroids = new_centroids;
}

int Kmeans::getNextInitialCentroidIndex() {
    // Adding the rest of the points according to the probability D(x)/SIGMA(D(x))
    // where D(x) is the distance between a datapoint x and it's nearest cluster

    auto total_distance = 0.0;
    for (auto const &p: _points)
        total_distance += p.getNearestClusterDistance();

    std::vector<double> probability(_points.size(), 0);
    for (int i = 0; i < _points.size(); i++)
        probability[i] = (_points[i].getNearestClusterDistance() / total_distance);

    for (int i = 0; i < _points.size(); i++)
        probability[i] += probability[i - 1];


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> random_real_gen(0, 1);
    auto rand_num = random_real_gen(gen);

    for (int i = 0; i < probability.size(); i++)
        if (rand_num < probability[i]) return i;

    return probability.size() - 1;
}

int Kmeans::getClosestCentroidIndex(const Point &point, const std::vector<Point> &centroids) {
    int closest_cluster = 0;
    double min_distance = INFINITY;

    for (int i = 0; i < centroids.size(); i++) {
        double dist = point.distance(centroids[i]);
        if (min_distance > dist) {
            min_distance = dist;
            closest_cluster = i;
        }
    }
    return closest_cluster;

}

bool Kmeans::equalCentroids(std::vector<Point> &a, std::vector<Point> &b) {
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

double Kmeans::calculateDistanceToCentroid(std::vector<Point> &vector, Point &point) {
    double dist = 0.0;

    for (Point &point: vector) {
        dist += point.distance(point);
    }
    return dist;
}

void Kmeans::printReport(std::vector<std::vector<Point> > &clusters, int iteration) {
    std::cout << "Iteration: " << iteration << '\n';
    for (int i = 0; i < clusters.size(); i++) {

        std::printf("Cluster %2d   No. of points: %3d   Distance: %5.2f,   Centroid location: ", i,
                    (int) clusters[i].size(), calculateDistanceToCentroid(clusters[i], _current_centroids[i]));
        std::cout << _current_centroids[i] << '\n';
    }
}

std::vector<std::vector<Point> > Kmeans::RunKMeansPP(int K, std::vector<Point> &centroids) {
    assert(K <= _points.size());
    _k = K;
    std::vector<std::vector<Point> > clusters(_k);

    int first_centroid = randomIndex();
    _initial_centroids.push_back(_points[first_centroid]);

    for (int i = 0; i < K - 1; i++) {
        updateNearestCluster(_initial_centroids);
        _initial_centroids.push_back(_points[getNextInitialCentroidIndex()]);
    }

    _current_centroids = _initial_centroids;

    int iteration = 0;


    do {
        _prev_centroids = _current_centroids;
        updateNearestCluster(_current_centroids);
        updateCentroids();

        auto temp = clusters;
        for (auto &point: _points)
            temp[point.getNearestClusterIndex()].push_back(point);

        printReport(temp, iteration);
        iteration++;

    } while (!equalCentroids(_current_centroids, _prev_centroids));

    for (auto &point: _points)
        clusters[point.getNearestClusterIndex()].push_back(point);

    centroids = _current_centroids;
    return clusters;
}


Kmeans::Kmeans(std::vector<Point> &input_data) : _points(input_data) {}

int Kmeans::randomIndex() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, _points.size() - 1);
    return dis(gen);
}


Kmeans::~Kmeans() = default;

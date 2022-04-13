#include <iostream>
#include "include/point.h"
#include "include/kmeans.h"
#include "include/utility.h"

int main() {
    auto filename = "../data/data.csv";
    auto point_coordinates = utility::loadDataSet(filename);
    auto data = utility::getPoints(point_coordinates);

    int K = 7;
    std::vector<Point> centroids;
    Kmeans KMPP(data);
    std::vector<std::vector<Point> > clusters_ = KMPP.RunKMeansPP(K, centroids);


    return 0;
}

#ifndef PERCEPTRON_PERCEPTRON_H
#define PERCEPTRON_PERCEPTRON_H

#include "Sample.h"
#include <vector>
#include "utils.h"


class perceptron {
    std::vector<double> _weights;
    double _alpha=0.01, _theta, _accuracy = 0.0;
    int _dimension = 0;

    void get_inner_product(const std::vector<double> &input, double *output) const;

    void update_weight(const std::vector<double> &x, double d);

    void generate_weights();

public:
    perceptron() {}

    ~perceptron() = default;

    void train(std::vector<sample> &sample_set);

    bool get_bool_output(const std::vector<double> &input) const;

    int getDimension() const;

    void setAlpha(double alpha);
};

#endif
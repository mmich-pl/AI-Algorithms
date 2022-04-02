#include <cassert>
#include <numeric>
#include <random>
#include <algorithm>
#include <iostream>
#include "../include/Perceptron.h"


void perceptron::get_inner_product(const std::vector<double> &input, double *output) const {
    assert(input.size() == _weights.size());
    *output = std::inner_product(input.begin(), input.end(), _weights.begin(), 0.0);
}

bool perceptron::get_bool_output(const std::vector<double> &input) const {
    double inner_product;
    get_inner_product(input, &inner_product);
    return (inner_product >= _theta?1:0);
}

void perceptron::update_weight(const std::vector<double> &x, double d) {
    for (auto i = 0; i < x.size(); i++)
        _weights[i] += x[i] * _alpha * d;
    _theta -= -1*_alpha * d;
}

void perceptron::generate_weights() {
    std::random_device rnd_device;
    std::mt19937 mersenne_engine{rnd_device()};
    std::uniform_real_distribution<> dist{-0.5, 0.5};

    std::generate(_weights.begin(), _weights.end(), [&dist, &mersenne_engine]() {
        return dist(mersenne_engine);
    });
    _theta=1;
}

void perceptron::train(std::vector<sample> &sample_set) {
    int iterations = 0;
    _dimension = sample_set[0].getData().size();
    auto sample_count = (double) sample_set.size();
    bool prediction, correct;

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(sample_set.begin(), sample_set.end(),g);

    _weights.resize(_dimension);
    generate_weights();

    std::cout << "Starting weights: ";
    utility::preety_print(_weights);

    while ( iterations <= 100) {
        iterations++;
        int error_count = 0;
        for (const auto &sample: sample_set) {
            prediction = get_bool_output(sample.getData());
            correct = sample.isOutput();
            if (prediction != correct) {
                error_count++;
                double error = (correct ? 1 : 0) - (prediction ? 1 : 0);
                update_weight(sample.getData(), error);
            }
        }
        _accuracy = (sample_count - error_count) / sample_count;
        printf("iteration: %d, error occured: %d, accuracy: %.2f\n", iterations, error_count, _accuracy);
    }
    std::cout << "Final weights: ";
    utility::preety_print(_weights);
}

int perceptron::getDimension() const {
    return _dimension;
}

void perceptron::setAlpha(double alpha) {
    _alpha = alpha;
}

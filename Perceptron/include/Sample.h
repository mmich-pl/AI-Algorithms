#ifndef PERCEPTRON_SAMPLE_H
#define PERCEPTRON_SAMPLE_H

#include <utility>
#include <vector>
#include <string>

class sample {
    bool _output;
    std::string _class;
    std::vector<double> _data;

public:

    sample(std::vector<double> &input, bool output, std::string group = "") : _data(input), _output(output),
                                                                              _class(std::move(group)) {}
    sample(std::vector<double> &input) : _data(input) {}

    bool isOutput() const;

    const std::vector<double> &getData() const;

    const int &getDataSize() const;

    const std::string &getClass() const;
};

#endif

#include "../include/Sample.h"

bool sample::isOutput() const {
    return _output;
}

const std::vector<double> &sample::getData() const {
    return _data;
}

const int &sample::getDataSize() const {
    return _data.size();
}

const std::string &sample::getClass() const {
    return _class;
}


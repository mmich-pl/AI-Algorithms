#include <iostream>
#include "../include/inputParser.h"


inputParser::inputParser(const std::string& line) {
    std::stringstream ss(line);

    for (std::string i; ss >> i;) {
        tokens.push_back(i);
        if (ss.peek() == ' ')
            ss.ignore();
    }
}

std::string inputParser::get_parameter(const std::string &option) const {
    auto it = std::find(tokens.begin(), tokens.end(), option);
    return (it != tokens.end() && ++it != tokens.end()) ? *it : "";
}

bool inputParser::flag_exist(std::string option) {
    return std::find(tokens.begin(), tokens.end(), option) != tokens.end();
}
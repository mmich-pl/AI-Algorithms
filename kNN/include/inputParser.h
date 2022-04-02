#ifndef KNN_INPUTPARSER_H
#define KNN_INPUTPARSER_H

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class inputParser {
private:
    std::vector <std::string> tokens;
public:
    inputParser(const std::string& input);

    bool flag_exist(std::string option);

    std::string get_parameter(const std::string &option) const;
};

#endif
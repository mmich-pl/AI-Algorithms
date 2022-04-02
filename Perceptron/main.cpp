#include <iostream>
#include <vector>
#include "include/Sample.h"
#include "include/Perceptron.h"
#include "include/inputParser.h"
#include "include/utils.h"

std::set<std::string> class_set;

std::vector<sample> training_set;
std::vector<sample> test_set;
perceptron *perceptron;

void fill_set(const std::string &filename, std::vector<sample> &dest) {
    class_set.clear();
    auto rows = utility::load_data_set(filename);
    std::vector<double> temp(rows[0].size() - 1);

    for (const auto &vec: rows) {
        class_set.insert(*(vec.end() - 1));
        if (class_set.size() > 2) throw std::logic_error("In input data should be only two different class_set.");

        std::transform(vec.begin(), vec.end() - 1,
                       temp.begin(), [](const std::string &val) { return std::stod(val); });

        dest.emplace_back(temp, (*(vec.end() - 1) == *class_set.begin()), *(vec.end() - 1));
    }
}

void start_test() {
    std::string c1 = *class_set.begin(), c2 = *std::next(class_set.begin(), 1);

    int invalid = 0, invalid_class1 = 0, invalid_class2 = 0;
    double tested = 0, tested_class1 = 0, tested_class2 = 0;

    for (const auto &aa: test_set) {
        tested++;

        bool out = perceptron->get_bool_output(aa.getData());
        aa.getClass() == c1 ? tested_class1++ : tested_class2++;

        if (out) {
            if (aa.getClass() != c1) {
                invalid_class2++;
                invalid++;
            }
        } else {
            tested_class2++;
            if (aa.getClass() != c2) {
                invalid_class1++;
                invalid++;
            }
        }
    }

    printf("%-20s accuracy: %.0f%%\n", c1.c_str(), (((tested_class1 - invalid_class1) / tested_class1)) * 100);
    printf("%-20s accuracy: %.0f%%\n", c2.c_str(), ((tested_class2 - invalid_class2) / tested_class2) * 100);
    printf("%-20s accuracy: %.0f%%\n", "Test", ((tested - invalid) / tested) * 100);
}

void get_user_input() {
    std::cout
            << "\nThe expected input is real or integer values separated by commas. "
               "Their amount must match the number of arguments in the test file. E.g. 4.5,7,2.6,0.2";
    std::string line{};
    std::cout << "\nEnter vector to match group or empty line to end: \n  >>";

    while (std::getline(std::cin, line) && !line.empty()) {
        std::vector<double> vec(perceptron->getDimension());
        line.erase(std::remove_if(line.begin(), line.end(),
                                  [](unsigned char x) { return std::isspace(x); }), line.end());
        std::stringstream ss(line);

        int j = 0;
        for (double i; ss >> i;) {
            vec[j++] = i;
            if (ss.peek() == ',')
                ss.ignore();
        }

        auto matching = perceptron->get_bool_output(vec);

        std::cout << "Tested point: ";
        utility::preety_print(vec);
        std::cout << "recognized group: " << (matching ? *class_set.begin() : *std::next(class_set.begin(), 1)) << "\n";
        std::cout << "  >>";
    }
}

int main() {
    inputParser *parser;
    std::string line{};
    std::cout << ">";

    while (std::getline(std::cin, line) && line != "-q") {
        parser = new inputParser(line);
        if (parser->flag_exist("-T")) {
            fill_set(parser->get_parameter("-T"), training_set);
            perceptron = new class perceptron();
            if (parser->flag_exist("-a"))
                perceptron ->setAlpha(std::stod(parser->get_parameter("-a")));
            perceptron->train(training_set);
            std::cout << "\nRecords loaded successfully.\n";
        }
        else {
            if (perceptron == nullptr) std::cout << "Load training data first!\n";
            else if (parser->flag_exist("-t")) {
                fill_set(parser->get_parameter("-t"), test_set);
                start_test();
            }
            else if (parser->flag_exist("-i"))
                get_user_input();
        }
        std::cout << ">";
    }

    return 0;
}

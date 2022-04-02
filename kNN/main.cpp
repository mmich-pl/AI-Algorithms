#include <iostream>
#include "include/point.h"
#include "include/kdTree.h"
#include "include/utility.h"
#include "include/inputParser.h"

kdTree *tree;

void run_test(const std::string &test_file) {
    auto test_set = utility::load_data_set(test_file);

    auto test_point = utility::get_points(test_set);
    std::map<std::string, int> recognized_cases = utility::get_groups(test_set),
            cases_in_file = recognized_cases;

    for (auto &point: test_point) {
        auto matching = tree->search_nearest(point);

        auto it = cases_in_file.find(point.get_group_name());
        if (it != cases_in_file.end()) it->second += 1;

        it = recognized_cases.find(matching);
        if (it != recognized_cases.end()) it->second += 1;

        std::cout << "Tested point: " << point << "\n";
        std::cout << "recognized group: " << matching << "\n";
        std::cout << "nodes visited: " << tree->visited() << "\n\n";
    }

    for (auto &entry: cases_in_file) {
        printf("%s: %d/%d\n", entry.first.c_str(),
               recognized_cases.find(entry.first)->second, entry.second);
    }
}

void load_manual() {
    auto in = utility::open_file_to_read("../data/help_sheet.txt");
    for (auto line = std::string(); std::getline(in, line);)
        std::cout << line << '\n';
}

void get_user_input() {
    std::cout
            << "\nThe expected input is real or integer values separated by commas. "
               "Their amount must match the number of arguments in the test file. E.g. 4.5,7,2.6,0.2";
    std::string line{};
    std::cout << "\nEnter vector to match group or empty line to end: \n  >>";

    while (std::getline(std::cin, line) && !line.empty()) {
        std::vector<double> vec(tree->_dimension + 1);
        line.erase(std::remove_if(line.begin(), line.end(),
                                  [](unsigned char x) { return std::isspace(x); }), line.end());
        std::stringstream ss(line);

        int j = 0;
        for (double i; ss >> i;) {
            vec[j++] = i;
            if (ss.peek() == ',')
                ss.ignore();
        }

        auto p = point(vec);
        auto matching = tree->search_nearest(p);

        std::cout << "Tested point: " << p << "\n";
        std::cout << "recognized group: " << matching << "\n";
        std::cout << "nodes visited: " << tree->visited() << "\n";
        std::cout << "  >>";
    }
}

int main() {
    load_manual();

    inputParser *parser;
    std::string line{};
    std::cout << ">";

    while (std::getline(std::cin, line) && line != "-q") {
        parser = new inputParser(line);
        if (parser->flag_exist("-T")) {
            tree = utility::create_kd_tree(parser->get_parameter("-T"));
            printf("%d records loaded successfully.\n", tree->get_nodes_amount());
        }
        else {
            if (tree == nullptr) std::cout << "Load training data first!\n";
            else if (parser->flag_exist("-t"))
                run_test(parser->get_parameter("-t"));
            else if (parser->flag_exist("-k"))
                tree->setK(std::stoi(parser->get_parameter("-k")));
            else if (parser->flag_exist("-i"))
                get_user_input();
        }
        std::cout << ">";
    }

    return 0;
}
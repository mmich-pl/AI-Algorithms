#include "../include/kdTree.h"

double kdTree::node::get_point_coordinate(size_t index) const {
    return _point.get_coordinate(index);
}

double kdTree::node::distance(const point &point) const {
    return _point.get_distance(point);
}

point kdTree::node::get_point() const {
    return _point;
}

kdTree::node::~node() = default;

kdTree::node *kdTree::make_tree(int begin, int end, int index) {
    if (end <= begin) return nullptr;

    int mid = begin + (end - begin) / 2;
    auto i = _nodes.begin();

    std::nth_element(i + begin, i + mid, i + end, nodeComparator(index));
    index = (index + 1) % _dimension;
    _nodes[mid]._left = make_tree(begin, mid, index);
    _nodes[mid]._right = make_tree(mid + 1, end, index);
    _nodes_amount++;
    return &_nodes[mid];
}

void kdTree::search_nearest(kdTree::node *root, const point &point, int index) {
    if (root == nullptr) return;
    ++_visited;
    auto dist = root->distance(point);
    _best_distance = dist;
    add_to_nearest_neighbours(root, dist);

    auto diff = root->get_point_coordinate(index) - point.get_coordinate(index);
    index = (index + 1) % point.get_dimension();
    search_nearest(diff > 0 ? root->_left : root->_right, point, index);
    if (pow(diff, 2) >= _best_distance) return;
    search_nearest(diff > 0 ? root->_right : root->_left, point, index);
}

int kdTree::visited() const {
    return _visited;
}

std::string kdTree::search_nearest(const point &point) {
    if (_root == nullptr) throw std::logic_error("Tree is empty");
    _nearest_neighbours.clear();
    _visited = 0;
    _best_distance = 0;
    search_nearest(_root, point, 0);
    return calculate_votes();
}

void kdTree::add_to_nearest_neighbours(kdTree::node *node, double distance) {
    if (_nearest_neighbours.size() >= _k) {

        auto max = std::max_element(_nearest_neighbours.begin(), _nearest_neighbours.end(),
                                    [](const std::pair<kdTree::node *, double> &a,
                                       const std::pair<kdTree::node *, double> &b) {
                                        return a.second < b.second;
                                    });
        _nearest_neighbours.erase(max);
    }
    _nearest_neighbours.emplace_back(node, distance);
}

std::string kdTree::calculate_votes() {

    for (const auto &pair: _nearest_neighbours) {
        auto it = _groups.find(pair.first->get_point().get_group_name());
        if (it != _groups.end()) it->second += 1;
    }

    auto max = std::max_element(_groups.begin(), _groups.end(),
                                [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
                                    return a.second < b.second;
                                });

    for (auto &item: _groups) {
        item.second = 0;
    }

    return max->first;
}

void kdTree::set_groups(const std::map<std::string, int> &groups) {
    kdTree::_groups = groups;
}

kdTree::~kdTree() {
    destroy_recursive(_root);

}

void kdTree::destroy_recursive(kdTree::node *node) {
    if (node) {
        destroy_recursive(node->_left);
        destroy_recursive(node->_right);
    }
    delete node;
}

void kdTree::setK(int k) {
    _k = k;
    std::cout << "Value of k updated!\n";
}

const int&kdTree::get_nodes_amount() const {
    return _nodes_amount;
}

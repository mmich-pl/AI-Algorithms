#ifndef KNN_KDTREE_H
#define KNN_KDTREE_H

#include <utility>
#include <algorithm>
#include <climits>
#include <map>

#include "point.h"

class kdTree {
private:
    struct node {
        point _point;
        node *_left, *_right;

        node(point point) : _point(std::move(point)), _left(nullptr), _right(nullptr) {}

        double get_point_coordinate(size_t index) const;

        double distance(const point &point) const;

        point get_point() const;

        ~node();
    };

    struct nodeComparator {
        size_t _index;

        explicit nodeComparator(size_t index) : _index(index) {}

        bool operator()(const node &x, const node &y) const {
            return x._point.get_coordinate(_index) < y._point.get_coordinate(_index);
        }
    };

    node *_root = nullptr;

    double _best_distance = std::numeric_limits<double>::max();
    int _k, _visited = 0, _nodes_amount = 0;
    std::vector<node> _nodes;
    std::map<std::string, int> _groups;
    std::vector<std::pair<node *, double>> _nearest_neighbours;

    node *make_tree(int begin, int end, int index);

    void search_nearest(node *root, const point &point, int index);

public:
    kdTree(const kdTree &) = delete;

    kdTree operator=(const kdTree &) = delete;

    template<typename iterator>
    kdTree(iterator begin, iterator end, int k=3) : _k(k), _nodes(begin, end) {
        _dimension = _nodes.begin()->_point.get_dimension();
        _root = make_tree(0, _nodes.size(), 0);
    }

    void setK(int k);

    int visited() const;

    std::string search_nearest(const point &point);

    void add_to_nearest_neighbours(node *node, double distance);

    std::string calculate_votes();

    void set_groups(const std::map<std::string, int> &groups);

    virtual ~kdTree();

    void destroy_recursive(node *node);

    int _dimension;

    const int &get_nodes_amount() const;
};

#endif

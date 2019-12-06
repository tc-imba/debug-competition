//
// Created by liu on 2019/11/26.
//

#include "segment_tree.h"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

segment_tree_value int_sum(const segment_tree_value a, const segment_tree_value b) {
    return segment_tree_value{.int_value=a.int_value + b.int_value};
}

segment_tree_value int_max(const segment_tree_value a, const segment_tree_value b) {
    return segment_tree_value{.int_value=max(a.int_value, b.int_value)};
}

segment_tree_value double_sum(const segment_tree_value a, const segment_tree_value b) {
    return segment_tree_value{.double_value=a.double_value + b.double_value};
}

int main() {
    unsigned int m, n;
    cin >> n >> m;

    vector<pair<unsigned int, unsigned int>> data_m;
    vector<pair<unsigned int, unsigned int>> data_n;
    unsigned int lines = 0;

    for (unsigned int i = 0; i < n; i++) {
        unsigned int a, b;
        cin >> a >> b;
        lines = max(lines, a);
        lines = max(lines, b);
        data_n.emplace_back(a, b);
    }

    for (unsigned int i = 0; i < m; i++) {
        unsigned int a, b;
        cin >> a >> b;
        lines = max(lines, a);
        lines = max(lines, b);
        data_m.emplace_back(a, b);
    }

    segment_tree tree_max = create_segment_tree(SEGMENT_TREE_INT, segment_tree_value{.int_value=0},
                                                int_sum, int_max, lines + 1);
    segment_tree tree_avg = create_segment_tree(SEGMENT_TREE_INT, segment_tree_value{.double_value=0.},
                                                double_sum, double_sum, lines + 1);

    for (const auto &p:data_n) {
        double avg = 1. / (p.second - p.first + 1);
        range_update_segment_tree(tree_max, segment_tree_value{.int_value=1}, p.first, p.second);
        range_update_segment_tree(tree_avg, segment_tree_value{.double_value=avg}, p.first, p.second);
    }

    for (const auto &p:data_m) {
        int max_bugs = aggregate_segment_tree(tree_max, p.first, p.second).int_value;
        double avg_bugs = aggregate_segment_tree(tree_avg, p.first, p.second).double_value;
        cout << fixed << setprecision(3) << avg_bugs << " " << max_bugs << endl;
    }

    free_segment_tree(tree_max);
    free_segment_tree(tree_avg);

    return 0;
}

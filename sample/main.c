#include "segment_tree.h"
#include <stdio.h>
#include <stdlib.h>

segment_tree_value int_sum(const segment_tree_value a, const segment_tree_value b) {
    return (segment_tree_value) (a.int_value + b.int_value);
}

segment_tree_value int_max(const segment_tree_value a, const segment_tree_value b) {
    return (segment_tree_value) (a.int_value > b.int_value ? a.int_value : b.int_value);
}

segment_tree_value double_sum(const segment_tree_value a, const segment_tree_value b) {
    return (segment_tree_value) (a.double_value + b.double_value);
}

unsigned int update_lines(unsigned int lines, unsigned num) {
    return lines > num ? lines : num;
}

int main() {
    unsigned int m, n;
    scanf("%u %u", &n, &m);
    unsigned int *data_n = malloc(2 * n * sizeof(unsigned int));
    unsigned int *data_m = malloc(2 * m * sizeof(unsigned int));
    unsigned int lines = 0;
    for (unsigned int i = 0; i < n; i++) {
        scanf("%u %u", &data_n[i * 2], &data_n[i * 2 + 1]);
        lines = update_lines(lines, data_n[i * 2]);
        lines = update_lines(lines, data_n[i * 2 + 1]);
    }
    for (unsigned int i = 0; i < m; i++) {
        scanf("%u %u", &data_m[i * 2], &data_m[i * 2 + 1]);
        lines = update_lines(lines, data_m[i * 2]);
        lines = update_lines(lines, data_m[i * 2 + 1]);
    }

    segment_tree tree_max = create_segment_tree(SEGMENT_TREE_INT, (segment_tree_value) 0,
                                                int_sum, int_max, lines + 1);
    segment_tree tree_avg = create_segment_tree(SEGMENT_TREE_INT, (segment_tree_value) 0.,
                                                double_sum, double_sum, lines + 1);

    for (unsigned int i = 0; i < n; i++) {
        unsigned int start = data_n[i * 2];
        unsigned int end = data_n[i * 2 + 1];
        double avg = 1. / (end - start + 1);
        range_update_segment_tree(tree_max, (segment_tree_value) 1, start, end);
        range_update_segment_tree(tree_avg, (segment_tree_value) avg, start, end);
    }

    for (unsigned int i = 0; i < m; i++) {
        unsigned int start = data_m[i * 2];
        unsigned int end = data_m[i * 2 + 1];
        int max_bugs = aggregate_segment_tree(tree_max, start, end).int_value;
        double avg_bugs = aggregate_segment_tree(tree_avg, start, end).double_value;
        printf("%.3lf %d\n", avg_bugs, max_bugs);
    }

    free(data_m);
    free(data_n);

    free_segment_tree(tree_max);
    free_segment_tree(tree_avg);

    return 0;
}
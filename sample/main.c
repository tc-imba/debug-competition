#include <stdio.h>
#include "segment_tree.h"

segment_tree_value int_add(const segment_tree_value a, const segment_tree_value b) {
    return (segment_tree_value) (a.int_value + b.int_value);
}

segment_tree_value int_max(const segment_tree_value a, const segment_tree_value b) {
    return (segment_tree_value) (a.int_value > b.int_value ? a.int_value : b.int_value);
}


int main() {
    printf("Hello, World!\n");
    unsigned int size = 1000;
    segment_tree tree = create_segment_tree(SEGMENT_TREE_INT, (segment_tree_value) 0, int_add, int_max, size);
    for (unsigned int i = 0; i < size; i++) {
        range_update_segment_tree(tree, (segment_tree_value) 1, 0, i);
    }
    for (unsigned int i = 0; i < size; i++) {
        segment_tree_value value = aggregate_segment_tree(tree, i, size - 1);
        printf("%d %d\n", i, value.int_value);
    }
    free_segment_tree(tree);
    return 0;
}
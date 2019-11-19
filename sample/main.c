#include "segment_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

segment_tree_value int_add(const segment_tree_value a, const segment_tree_value b) {
    return (segment_tree_value) (a.int_value + b.int_value);
}

segment_tree_value int_max(const segment_tree_value a, const segment_tree_value b) {
    return (segment_tree_value) (a.int_value > b.int_value ? a.int_value : b.int_value);
}

segment_tree_value str_add(const segment_tree_value a, const segment_tree_value b) {
    size_t la = strlen(a.str_value), lb = strlen(b.str_value);
    segment_tree_value value;
    value.str_value = malloc(1 + la + lb);
    strcpy(value.str_value, a.str_value);
    strcpy(value.str_value + la, b.str_value);
    return value;
}

int main() {
    printf("Hello, World!\n");
    unsigned int size = 100;
    segment_tree tree = create_segment_tree(SEGMENT_TREE_INT, (segment_tree_value) 0, int_add, int_max, size);
    for (unsigned int i = 0; i < size; i++) {
        range_update_segment_tree(tree, (segment_tree_value) 1, 0, i);
    }
    for (unsigned int i = 0; i < size; i++) {
        segment_tree_value value = aggregate_segment_tree(tree, i, size - 1);
        printf("%d %d\n", i, value.int_value);
    }
    free_segment_tree(tree);

    tree = create_segment_tree(SEGMENT_TREE_STR, (segment_tree_value) "", str_add, str_add, 10);
    for (int i = 0; i < 10; i++) {
        char temp[2] = {};
        temp[0] = '0' + i;
        range_update_segment_tree(tree, (segment_tree_value) temp, 0, i);
    }
    segment_tree_value value = aggregate_segment_tree(tree, 0, 9);
    printf("%s\n", value.str_value);
    free(value.str_value);
    value = get_element_segment_tree(tree, 0);
    printf("%s\n", value.str_value);
    free(value.str_value);
    free_segment_tree(tree);
    return 0;
}
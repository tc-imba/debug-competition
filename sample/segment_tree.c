//
// Created by liu on 2019/11/15.
//

#include "segment_tree.h"
#include <stdlib.h>
#include <string.h>

typedef struct segment_tree_impl_t {
    segment_tree_value *array;
    segment_tree_value_type value_type;
    segment_tree_function operation;
    segment_tree_function aggregation;
    unsigned int size;
} segment_tree_impl;

static void create_segment_tree_helper(segment_tree_impl *tree, const segment_tree_value initial_value,
                                       unsigned int index, unsigned int left, unsigned int right) {
    // Use a heap to store the segment tree data
    // You can either use a real tree
    if (left == right) {
        if (tree->value_type == SEGMENT_TREE_STR) {
            segment_tree_value value;
            value.str_value = malloc(1 + strlen(initial_value.str_value));
            strcpy(value.str_value, initial_value.str_value);
            tree->array[index] = value;
        } else {
            tree->array[index] = initial_value;
        }
    } else {
        unsigned int middle = (left + right) / 2;
        create_segment_tree_helper(tree, initial_value, index * 2, left, middle);
        create_segment_tree_helper(tree, initial_value, index * 2 + 1, middle + 1, right);
        tree->array[index] = tree->aggregation(tree->array[index * 2], tree->array[index * 2 + 1]);
    }
}

segment_tree create_segment_tree(segment_tree_value_type value_type,
                                 const segment_tree_value initial_value,
                                 segment_tree_function operation,
                                 segment_tree_function aggregation,
                                 unsigned int size) {
    segment_tree_impl *tree = malloc(sizeof(segment_tree_impl));
    tree->value_type = value_type;
    tree->operation = operation;
    tree->aggregation = aggregation;
    tree->size = size;
    tree->array = malloc(4 * size * sizeof(segment_tree_value)); // use 4 * size for convenience
    create_segment_tree_helper(tree, initial_value, 1, 0, size - 1);
    return (segment_tree) tree;
}

static void update_segment_tree_helper(segment_tree_impl *tree, const segment_tree_value value, unsigned int pos,
                                       unsigned int index, unsigned int left, unsigned int right) {
    segment_tree_value new_value;
    if (left == right) {
        new_value = tree->operation(tree->array[index], value);
    } else {
        unsigned int middle = (left + right) / 2;
        if (pos <= middle) {
            update_segment_tree_helper(tree, value, pos, index * 2, left, middle);
        } else {
            update_segment_tree_helper(tree, value, pos, index * 2 + 1, middle + 1, right);
        }
        new_value = tree->aggregation(tree->array[index * 2], tree->array[index * 2 + 1]);
    }
    if (tree->value_type == SEGMENT_TREE_STR) {
        free(tree->array[index].str_value);
    }
    tree->array[index] = new_value;
}

void update_segment_tree(segment_tree tree, const segment_tree_value value, unsigned int pos) {
    segment_tree_impl *_tree = tree;
    update_segment_tree_helper(_tree, value, pos, 1, 0, _tree->size - 1);
}

void
range_update_segment_tree(segment_tree tree, const segment_tree_value value, unsigned int start, unsigned int end) {
    // This is a very naive implementation
    // You can use lazy propagation to improve it
    // See https://cp-algorithms.com/data_structures/segment_tree.html#toc-tgt-9
    for (unsigned int i = start; i <= end; i++) {
        update_segment_tree(tree, value, i);
    }
}

static segment_tree_value aggregate_segment_tree_helper(const segment_tree_impl *tree,
                                                        unsigned int start, unsigned int end,
                                                        unsigned int index, unsigned int left, unsigned int right) {
    if (start == left && end == right) {
        if (tree->value_type == SEGMENT_TREE_STR) {
            segment_tree_value value;
            value.str_value = malloc(1 + strlen(tree->array[index].str_value));
            strcpy(value.str_value, tree->array[index].str_value);
            return value;
        } else {
            return tree->array[index];
        }
    } else {
        unsigned middle = (left + right) / 2;
        unsigned _right = end < middle ? end : middle;
        unsigned _left = start > (middle + 1) ? start : (middle + 1);
        if (start > _right) {
            return aggregate_segment_tree_helper(tree, _left, end, index * 2 + 1, middle + 1, right);
        } else if (_left > end) {
            return aggregate_segment_tree_helper(tree, start, _right, index * 2, left, middle);
        } else {
            segment_tree_value value_left = aggregate_segment_tree_helper(
                    tree, start, _right, index * 2, left, middle);
            segment_tree_value value_right = aggregate_segment_tree_helper(
                    tree, _left, end, index * 2 + 1, middle + 1, right);
            segment_tree_value value = tree->aggregation(value_left, value_right);
            if (tree->value_type == SEGMENT_TREE_STR) {
                free(value_left.str_value);
                free(value_right.str_value);
            }
            return value;
        }
    }
}

segment_tree_value get_element_segment_tree(const_segment_tree tree, unsigned int pos) {
    const segment_tree_impl *_tree = tree;
    return aggregate_segment_tree_helper(_tree, pos, pos, 1, 0, _tree->size - 1);
}

segment_tree_value aggregate_segment_tree(const_segment_tree tree, unsigned int start, unsigned int end) {
    const segment_tree_impl *_tree = tree;
    return aggregate_segment_tree_helper(_tree, start, end, 1, 0, _tree->size - 1);
}

static void free_segment_tree_helper(segment_tree_impl *tree,
                                     unsigned int index, unsigned int left, unsigned int right) {
    // just a reverse of the create helper
    // only be called when SEGMENT_TREE_STR
    if (left == right) {
        free(tree->array[index].str_value);
    } else {
        unsigned int middle = (left + right) / 2;
        free_segment_tree_helper(tree, index * 2, left, middle);
        free_segment_tree_helper(tree, index * 2 + 1, middle + 1, right);
        free(tree->array[index].str_value);
    }
}

void free_segment_tree(segment_tree tree) {
    segment_tree_impl *_tree = tree;
    if (_tree->value_type == SEGMENT_TREE_STR) {
        free_segment_tree_helper(_tree, 1, 0, _tree->size - 1);
    }
    free(_tree->array);
    free(_tree);
}



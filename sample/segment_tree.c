//
// Created by liu on 2019/11/15.
//

#include "segment_tree.h"
#include <stdlib.h>

typedef struct segment_tree_impl_t {
    segment_tree_value *array;
    segment_tree_value_type value_type;
    segment_tree_operation operation;
    segment_tree_aggregation aggregation;
    unsigned int size;
} segment_tree_impl;

static void create_segment_tree_helper(segment_tree_impl *tree, segment_tree_value initial_value,
                                unsigned int index, unsigned int left, unsigned int right) {
    // Use a heap to store the segment tree data
    // You can either use a real tree
    if (left == right) {
        tree->array[index] = initial_value;
    } else {
        unsigned int middle = (left + right) / 2;
        create_segment_tree_helper(tree, initial_value, index * 2, left, middle);
        create_segment_tree_helper(tree, initial_value, index * 2 + 1, middle + 1, right);
        tree->array[index] = tree->aggregation(tree->array[index * 2], tree->array[index * 2 + 1]);
    }
}

segment_tree create_segment_tree(segment_tree_value_type value_type,
                                 segment_tree_value initial_value,
                                 segment_tree_operation operation,
                                 segment_tree_aggregation aggregation,
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

static void update_segment_tree_helper(segment_tree_impl *tree, segment_tree_value value, unsigned int pos,
                                unsigned int index, unsigned int left, unsigned int right) {
    if (left == right) {
        tree->array[index] = tree->operation(tree->array[index], value);
    } else {
        unsigned int middle = (left + right) / 2;
        if (pos <= middle) {
            update_segment_tree_helper(tree, value, pos, index * 2, left, middle);
        } else {
            update_segment_tree_helper(tree, value, pos, index * 2 + 1, middle + 1, right);
        }
        tree->array[index] = tree->aggregation(tree->array[index * 2], tree->array[index * 2 + 1]);
    }
}

void update_segment_tree(segment_tree tree, segment_tree_value value, unsigned int pos) {
    segment_tree_impl *_tree = tree;
    update_segment_tree_helper(_tree, value, pos, 1, 0, _tree->size - 1);
}

void range_update_segment_tree(segment_tree tree, segment_tree_value value, unsigned int start, unsigned int end) {
    // This is a very naive implementation
    // You can use lazy propagation to improve it
    // See https://cp-algorithms.com/data_structures/segment_tree.html#toc-tgt-9
    for (unsigned int i = start; i <= end; i++) {
        update_segment_tree(tree, value, i);
    }
}

static segment_tree_value aggregate_segment_tree_helper(const segment_tree_impl *tree, unsigned int start, unsigned int end,
                                                 unsigned int index, unsigned int left, unsigned int right) {
    if (start == left && end == right) {
        return tree->array[index];
    } else {
        unsigned middle = (left + right) / 2;
        unsigned _right = end < middle ? end : middle;
        unsigned _left = start > (middle + 1) ? start : (middle + 1);
        if (start > _right) {
            return aggregate_segment_tree_helper(tree, _left, end, index * 2 + 1, middle + 1, right);
        } else if (_left > end) {
            return aggregate_segment_tree_helper(tree, start, _right, index * 2, left, middle);
        } else {
            return tree->aggregation(
                    aggregate_segment_tree_helper(tree, start, _right, index * 2, left, middle),
                    aggregate_segment_tree_helper(tree, _left, end, index * 2 + 1, middle + 1, right)
            );
        }
    }
}

segment_tree_value aggregate_segment_tree(const_segment_tree tree, unsigned int start, unsigned int end) {
    const segment_tree_impl *_tree = tree;
    return aggregate_segment_tree_helper(_tree, start, end, 1, 0, _tree->size - 1);
}

void free_segment_tree(segment_tree tree) {
    segment_tree_impl *_tree = tree;
    free(_tree->array);
    free(_tree);
}

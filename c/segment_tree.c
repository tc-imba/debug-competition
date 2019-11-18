//
// Created by liu on 2019/11/15.
//

#include "segment_tree.h"
#include <stdlib.h>

typedef struct segment_tree_node_t {

} segment_tree_node;

typedef struct segment_tree_impl_t {
    segment_tree_node *root;
    segment_tree_value_type value_type;
    segment_tree_comparator comparator;
    unsigned int size;
} segment_tree_impl;


segment_tree create_segment_tree(segment_tree_value_type value_type,
                                 segment_tree_comparator comparator,
                                 unsigned int size) {
    segment_tree_impl *tree = malloc(sizeof(segment_tree_impl));
    tree->root = malloc(sizeof(segment_tree_node));
    tree->value_type = value_type;
    tree->comparator = comparator;
    tree->size = size;
    return (segment_tree) tree;
}

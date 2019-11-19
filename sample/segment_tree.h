//
// Created by liu on 2019/11/15.
//

#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

// Data type stored in the segment tree
typedef enum segment_tree_value_type_t {
    SEGMENT_TREE_INT = 0x01, // segment tree contains int values
    SEGMENT_TREE_STR = 0x02, // segment tree contains char* (string) values
    SEGMENT_TREE_DOUBLE = 0x03, // segment tree contains double values
    SEGMENT_TREE_UNKNOWN = 0x00
} segment_tree_value_type;

// The value stored in the segment tree
// Research online what an "union" is.
typedef union segment_tree_value_t {
    int int_value;
    double double_value;
    char *str_value;
} segment_tree_value;

typedef void *segment_tree;
typedef const void *const_segment_tree;

typedef segment_tree_value (*segment_tree_function)(const segment_tree_value, const segment_tree_value);
// REQUIRES: the value type of two values are the same
// EFFECTS : return a new value based on the two values,
//           if value type is SEGMENT_TREE_STR, memory should be allocated for the return value

segment_tree create_segment_tree(segment_tree_value_type value_type,
                                 segment_tree_value initial_value,
                                 segment_tree_function operation,
                                 segment_tree_function aggregation,
                                 unsigned int size);
// REQUIRES: argument 'size' in the range [1, 2^32-1]
// EFFECTS : return a new created segment_tree

void update_segment_tree(segment_tree tree, segment_tree_value value, unsigned int pos);
// REQUIRES: argument 'tree' is not null and is a valid segment tree,
//           type instantiated in argument 'value' corresponds to the value_type in the segment tree,
//           argument 'pos' in the range [0, tree.size-1]
// EFFECTS : update the specific position of the tree with the 'operation' function,
//           argument 'value' should not be modified
// MODIFIES: modifies 'tree'

void range_update_segment_tree(segment_tree tree, segment_tree_value value, unsigned int start, unsigned int end);
// REQUIRES: argument 'tree' is not null and is a valid segment tree,
//           type instantiated in argument 'value' corresponds to the value_type in the segment tree,
//           argument 'start' and 'end' in the range [0, tree.size-1], and 'start' <= 'end'
// EFFECTS : update the interval [start, end] of the tree with the 'operation' function,
//           argument 'value' should not be modified
// MODIFIES: modifies 'tree'

segment_tree_value get_element_segment_tree(const_segment_tree tree, unsigned int pos);
// REQUIRES: argument 'tree' is not null and is a valid segment tree,
//           type instantiated in argument 'value' corresponds to the value_type in the segment tree,
//           argument 'pos' in the range [0, tree.size-1]
// EFFECTS : return the value at the specific position of the tree,
//           anything in 'tree' should not be modified,
//           if value type is SEGMENT_TREE_STR, memory should be allocated for the return value

segment_tree_value aggregate_segment_tree(const_segment_tree tree, unsigned int start, unsigned int end);
// REQUIRES: argument 'tree' is not null and is a valid segment tree,
//           type instantiated in argument 'value' corresponds to the value_type in the segment tree,
//           argument 'start' and 'end' in the range [0, tree.size-1], and 'start' <= 'end'
// EFFECTS : aggregate the interval [start, end] of the tree with the 'aggregation' function,
//           anything in 'tree' should not be modified,
//           if value type is SEGMENT_TREE_STR, memory should be allocated for the return value

void free_segment_tree(segment_tree tree);
// REQUIRES: argument 'tree' is not null and is a valid segment tree,
// EFFECTS : free all memory allocated by the segment tree

#endif //SEGMENT_TREE_H

//
// Created by liu on 2019/11/15.
//

#ifndef C_SEGMENT_TREE_H
#define C_SEGMENT_TREE_H

// Data type stored in the segment tree
typedef enum segment_tree_value_type_t {
    SEGMENT_TREE_INT = 0x01, // segment tree contains int values
    SEGMENT_TREE_STR = 0x02, // segment tree contains char* values
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

typedef segment_tree_value (*segment_tree_operation)(const segment_tree_value, const segment_tree_value);
typedef segment_tree_value (*segment_tree_aggregation)(const segment_tree_value, const segment_tree_value);

segment_tree create_segment_tree(segment_tree_value_type value_type,
                                 segment_tree_value initial_value,
                                 segment_tree_operation operation,
                                 segment_tree_aggregation aggregation,
                                 unsigned int size);

void update_segment_tree(segment_tree tree, segment_tree_value value, unsigned int pos);

// update the segment tree in range [start, end]
void range_update_segment_tree(segment_tree tree, segment_tree_value value, unsigned int start, unsigned int end);

// aggregate the segment tree in range [start, end]
segment_tree_value aggregate_segment_tree(segment_tree tree, unsigned int start, unsigned int end);

void free_segment_tree(segment_tree tree);

#endif //C_SEGMENT_TREE_H

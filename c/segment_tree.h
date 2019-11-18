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

typedef int (*segment_tree_comparator)(const segment_tree_value a, const segment_tree_value b);

segment_tree create_segment_tree(segment_tree_value_type value_type,
                                 segment_tree_comparator comparator,
                                 unsigned int size);



#endif //C_SEGMENT_TREE_H

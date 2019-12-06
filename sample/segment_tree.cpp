//
// Created by liu on 2019/11/26.
//

#include "segment_tree.h"
#include <vector>
#include <cstring>
#include <cstdlib>

class SegmentTree {
private:
    std::vector<segment_tree_value> array;
    segment_tree_value_type value_type;
    segment_tree_function operation;
    segment_tree_function aggregation;
    unsigned int size;

    void init(const segment_tree_value initial_value,
              unsigned int index, unsigned int left, unsigned int right) {
        // Use a heap to store the segment tree data
        // You can either use a real tree
        if (left == right) {
            if (value_type == SEGMENT_TREE_STR) {
                segment_tree_value value;
                value.str_value = (char *) malloc(1 + strlen(initial_value.str_value));
                strcpy(value.str_value, initial_value.str_value);
                array[index] = value;
            } else {
                array[index] = initial_value;
            }
        } else {
            unsigned int middle = (left + right) / 2;
            init(initial_value, index * 2, left, middle);
            init(initial_value, index * 2 + 1, middle + 1, right);
            array[index] = aggregation(array[index * 2], array[index * 2 + 1]);
        }
    }

    void update(const segment_tree_value value, unsigned int pos,
                unsigned int index, unsigned int left, unsigned int right) {
        segment_tree_value new_value;
        if (left == right) {
            new_value = operation(array[index], value);
        } else {
            unsigned int middle = (left + right) / 2;
            if (pos <= middle) {
                update(value, pos, index * 2, left, middle);
            } else {
                update(value, pos, index * 2 + 1, middle + 1, right);
            }
            new_value = aggregation(array[index * 2], array[index * 2 + 1]);
        }
        if (value_type == SEGMENT_TREE_STR) {
            free(array[index].str_value);
        }
        array[index] = new_value;
    }

    segment_tree_value aggregate(unsigned int start, unsigned int end,
                                 unsigned int index, unsigned int left, unsigned int right) {
        if (start == left && end == right) {
            if (value_type == SEGMENT_TREE_STR) {
                segment_tree_value value;
                value.str_value = (char *) malloc(1 + strlen(array[index].str_value));
                strcpy(value.str_value, array[index].str_value);
                return value;
            } else {
                return array[index];
            }
        } else {
            unsigned middle = (left + right) / 2;
            unsigned _right = end < middle ? end : middle;
            unsigned _left = start > (middle + 1) ? start : (middle + 1);
            if (start > _right) {
                return aggregate(_left, end, index * 2 + 1, middle + 1, right);
            } else if (_left > end) {
                return aggregate(start, _right, index * 2, left, middle);
            } else {
                segment_tree_value value_left = aggregate(
                        start, _right, index * 2, left, middle);
                segment_tree_value value_right = aggregate(
                        _left, end, index * 2 + 1, middle + 1, right);
                segment_tree_value value = aggregation(value_left, value_right);
                if (value_type == SEGMENT_TREE_STR) {
                    free(value_left.str_value);
                    free(value_right.str_value);
                }
                return value;
            }
        }
    }

    void destruct(unsigned int index, unsigned int left, unsigned int right) {
        // just a reverse of init
        // only be called when SEGMENT_TREE_STR
        if (left == right) {
            free(array[index].str_value);
        } else {
            unsigned int middle = (left + right) / 2;
            destruct(index * 2, left, middle);
            destruct(index * 2 + 1, middle + 1, right);
            free(array[index].str_value);
        }
    }

public:
    SegmentTree(segment_tree_value_type value_type,
                const segment_tree_value initial_value,
                segment_tree_function operation,
                segment_tree_function aggregation,
                unsigned int size) :
            value_type(value_type), operation(operation), aggregation(aggregation), size(size) {
        array.resize(4 * size);
        init(initial_value, 1, 0, size - 1);
    }

    ~SegmentTree() {
        if (value_type == SEGMENT_TREE_STR) {
            destruct(1, 0, size - 1);
        }
    }

    void update(const segment_tree_value value, unsigned int pos) {
        update(value, pos, 1, 0, size - 1);
    }

    void update(const segment_tree_value value, unsigned int start, unsigned int end) {
        // This is a very naive implementation
        // You can use lazy propagation to improve it
        // See https://cp-algorithms.com/data_structures/segment_tree.html#toc-tgt-9
        for (unsigned int i = start; i <= end; i++) {
            update(value, i);
        }
    }

    segment_tree_value aggregate(unsigned int pos) {
        return aggregate(pos, pos, 1, 0, size - 1);
    }

    segment_tree_value aggregate(unsigned int start, unsigned int end) {
        return aggregate(start, end, 1, 0, size - 1);
    }
};

segment_tree create_segment_tree(segment_tree_value_type value_type,
                                 const segment_tree_value initial_value,
                                 segment_tree_function operation,
                                 segment_tree_function aggregation,
                                 unsigned int size) {
    auto tree = new SegmentTree(value_type, initial_value, operation, aggregation, size);
    return (segment_tree) tree;
}

void update_segment_tree(segment_tree tree, const segment_tree_value value, unsigned int pos) {
    ((SegmentTree *) tree)->update(value, pos);
}

void
range_update_segment_tree(segment_tree tree, const segment_tree_value value, unsigned int start, unsigned int end) {
    ((SegmentTree *) tree)->update(value, start, end);
}

segment_tree_value get_element_segment_tree(const_segment_tree tree, unsigned int pos) {
    return ((SegmentTree *) tree)->aggregate(pos);
}

segment_tree_value aggregate_segment_tree(const_segment_tree tree, unsigned int start, unsigned int end) {
    return ((SegmentTree *) tree)->aggregate(start, end);
}

void free_segment_tree(segment_tree tree) {
    delete ((SegmentTree *) tree);
}

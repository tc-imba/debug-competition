//
// Created by liu on 2019/11/20.
//
#ifdef DEBUG_C
extern "C" {
#endif

#include "segment_tree.h"

#ifdef DEBUG_C
}
#endif

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <unordered_map>

using namespace std;

namespace segment_tree_functions {

    segment_tree_value int_sum(const segment_tree_value a, const segment_tree_value b) {
        return segment_tree_value{.int_value = a.int_value + b.int_value};
    }

    segment_tree_value int_min(const segment_tree_value a, const segment_tree_value b) {
        return segment_tree_value{.int_value = min(a.int_value, b.int_value)};
    }

    segment_tree_value int_max(const segment_tree_value a, const segment_tree_value b) {
        return segment_tree_value{.int_value = max(a.int_value, b.int_value)};
    }

    segment_tree_value double_sum(const segment_tree_value a, const segment_tree_value b) {
        return segment_tree_value{.double_value = a.double_value + b.double_value};
    }

    segment_tree_value double_min(const segment_tree_value a, const segment_tree_value b) {
        return segment_tree_value{.double_value = min(a.double_value, b.double_value)};
    }

    segment_tree_value double_max(const segment_tree_value a, const segment_tree_value b) {
        return segment_tree_value{.double_value = max(a.double_value, b.double_value)};
    }

    segment_tree_value str_sum(const segment_tree_value a, const segment_tree_value b) {
        size_t la = strlen(a.str_value), lb = strlen(b.str_value);
        segment_tree_value value;
        value.str_value = (char *) malloc(1 + la + lb);
        strcpy(value.str_value, a.str_value);
        strcpy(value.str_value + la, b.str_value);
        return value;
    }

    segment_tree_value str_min(const segment_tree_value a, const segment_tree_value b) {
        segment_tree_value value;
        if (strcmp(a.str_value, b.str_value) <= 0) {
            value.str_value = (char *) malloc(1 + strlen(a.str_value));
            strcpy(value.str_value, a.str_value);
        } else {
            value.str_value = (char *) malloc(1 + strlen(b.str_value));
            strcpy(value.str_value, b.str_value);
        }
        return value;
    }

    segment_tree_value str_max(const segment_tree_value a, const segment_tree_value b) {
        segment_tree_value value;
        if (strcmp(a.str_value, b.str_value) >= 0) {
            value.str_value = (char *) malloc(1 + strlen(a.str_value));
            strcpy(value.str_value, a.str_value);
        } else {
            value.str_value = (char *) malloc(1 + strlen(b.str_value));
            strcpy(value.str_value, b.str_value);
        }
        return value;
    }
}


int main() {
    unordered_map<string, segment_tree_value_type> segment_tree_value_type_map = {
            {"int",    SEGMENT_TREE_INT},
            {"str",    SEGMENT_TREE_STR},
            {"double", SEGMENT_TREE_DOUBLE},
    };

    unordered_map<string, segment_tree_function> segment_tree_function_map = {
            {"int_sum",    segment_tree_functions::int_sum},
            {"int_min",    segment_tree_functions::int_min},
            {"int_max",    segment_tree_functions::int_max},
            {"str_sum",    segment_tree_functions::str_sum},
            {"str_min",    segment_tree_functions::str_min},
            {"str_max",    segment_tree_functions::str_max},
            {"double_sum", segment_tree_functions::double_sum},
            {"double_min", segment_tree_functions::double_min},
            {"double_max", segment_tree_functions::double_max},
    };

    string value_type_str, operation_str, aggregation_str;
    unsigned int n, m; // n: size, m: query number
    cin >> n >> m >> value_type_str >> operation_str >> aggregation_str;
    auto value_type = segment_tree_value_type_map.at(value_type_str);
    auto operation = segment_tree_function_map.at(value_type_str + "_" + operation_str);
    auto aggregation = segment_tree_function_map.at(value_type_str + "_" + aggregation_str);

    segment_tree_value initial_value;
    string initial_value_string;
    switch (value_type) {
        case SEGMENT_TREE_INT:
            cin >> initial_value.int_value;
            break;
        case SEGMENT_TREE_DOUBLE:
            cin >> initial_value.double_value;
            break;
        case SEGMENT_TREE_STR:
            cin >> initial_value_string;
            initial_value.str_value = (char *) initial_value_string.c_str();
            break;
        default:
            assert(0);
    }
    auto tree = create_segment_tree(value_type, initial_value, operation, aggregation, n);

    for (unsigned int i = 0; i < m; i++) {
        string op;
        unsigned start, end;
        cin >> op;
        if (op == "update" || op == "range") {
            segment_tree_value value;
            switch (value_type) {
                case SEGMENT_TREE_INT:
                    cin >> value.int_value;
                    break;
                case SEGMENT_TREE_DOUBLE:
                    cin >> value.double_value;
                    break;
                case SEGMENT_TREE_STR: {
                    string temp;
                    cin >> temp;
                    value.str_value = (char *) malloc(1 + temp.length());
                    strcpy(value.str_value, temp.c_str());
                    break;
                }
                default:
                    assert(0);
            }
            if (op == "update") {
                cin >> start;
                update_segment_tree(tree, value, start);
            } else {
                cin >> start >> end;
                range_update_segment_tree(tree, value, start, end);
            }
            if (value_type == SEGMENT_TREE_STR) {
                free(value.str_value);
            }
        } else if (op == "get" || op == "aggregate") {
            segment_tree_value value;
            if (op == "get") {
                cin >> start;
                value = get_element_segment_tree(tree, start);
            } else {
                cin >> start >> end;
                value = aggregate_segment_tree(tree, start, end);
            }
            switch (value_type) {
                case SEGMENT_TREE_INT:
                    cout << value.int_value << endl;
                    break;
                case SEGMENT_TREE_DOUBLE:
                    cout << value.double_value << endl;
                    break;
                case SEGMENT_TREE_STR:
                    cout << value.str_value << endl;
                    break;
                default:
                    assert(0);
            }
            if (value_type == SEGMENT_TREE_STR) {
                free(value.str_value);
            }
        } else {
            assert(0);
        }
    }
    free_segment_tree(tree);
    return 0;
}


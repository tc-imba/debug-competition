#!/usr/bin/env bash

exit_on_failure() {
    if [ $? -ne 0 ]; then
        echo ""
        echo "build failed"
        exit 1
    fi
}

echo "build debug: "
clang -Wall -Werror -O2 -std=c11 -o /out/segment_tree.o -I /in/sample -c /in/segment_tree.c
clang -Wall -Werror -O2 -std=c11 -o /out/debug -I /in/sample /in/main.c /out/segment_tree.o
exit_on_failure
echo "finished"
echo ""

echo "build debug_test: "
clang++ -Wall -Werror -O2 -std=c++17 -o /out/debug_test -I /in/sample /in/sample/test.cpp /out/segment_tree.o
exit_on_failure
echo "finished"
echo ""

echo "all tasks finished, build successfully"




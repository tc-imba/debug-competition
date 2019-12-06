#!/usr/bin/env bash

OPTIONS="-Wall -Werror -O2 -g -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer"

exit_on_failure() {
    if [ $? -ne 0 ]; then
        echo ""
        echo "build failed"
        exit 1
    fi
}

echo "build debug: "
clang $OPTIONS -std=c11 -o /out/segment_tree.o -I /in/sample -c /in/segment_tree.c
clang $OPTIONS -std=c11 -o /out/debug -I /in/sample /in/main.c /out/segment_tree.o
exit_on_failure
echo "finished"
echo ""

echo "build debug_test: "
clang++ -DDEBUG_C $OPTIONS -std=c++17 -o /out/debug_test -I /in/sample /in/sample/test.cpp /out/segment_tree.o
exit_on_failure
echo "finished"
echo ""

echo "all tasks finished, build successfully"




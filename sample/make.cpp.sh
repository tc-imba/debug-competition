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
clang++ $OPTIONS -std=c++17 -o /out/debug -I /in/sample /in/main.cpp /in/segment_tree.cpp
exit_on_failure
echo "finished"
echo ""

echo "build debug_test: "
clang++ $OPTIONS -std=c++17 -o /out/debug_test -I /in/sample /in/sample/test.cpp /in/segment_tree.cpp
exit_on_failure
echo "finished"
echo ""

echo "all tasks finished, build successfully"




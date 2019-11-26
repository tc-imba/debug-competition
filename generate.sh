#!/bin/bash

BUILD_DIR=cmake-build-release
GENERATE_EXEC=$BUILD_DIR/debug_generate
DATA_EXEC=$BUILD_DIR/debug_test
BUG_EXEC=$BUILD_DIR/debug_cpp

rm -rf test-cases
$GENERATE_EXEC

for f in `ls test-cases/data.*.in`; do
    echo $f
    $DATA_EXEC < $f > ${f%%.in}.out
done

for f in `ls test-cases/bug.*.in`; do
    echo $f
    $BUG_EXEC < $f > ${f%%.in}.out
done


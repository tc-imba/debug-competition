#!/usr/bin/env bash

BUILD_DIR=cmake-build-release
GENERATE_EXEC=$BUILD_DIR/debug_generate
DATA_EXEC=$BUILD_DIR/debug_test
BUG_EXEC=$BUILD_DIR/debug_cpp

rm -rf test-cases
cp config.template.yaml config.yaml
$GENERATE_EXEC

for f in `ls test-cases/data.*.in`; do
    echo $f
    name=${f%%.in}
    $DATA_EXEC < $name.in > $name.out
    echo "  - <<: *default
    input: $name.in
    output: $name.out
    execute_file: debug_test
    execute_args: debug_test" >> config.yaml
done

for f in `ls test-cases/bug.*.in`; do
    echo $f
    name=${f%%.in}
    $BUG_EXEC < $name.in > $name.out
    echo "  - <<: *default
    input: $name.in
    output: $name.out
    execute_file: debug
    execute_args: debug" >> config.yaml
done

zip -r debug.zip config.yaml test-cases/* sample/*.sh sample/test.cpp sample/segment_tree.h

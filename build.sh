#!/bin/bash

input="./include/ectest_master.h"

mkdir -p ./build/
echo "#ifndef ECTEST_H__" > ./build/ectest.h
echo "#define ECTEST_H__" >> ./build/ectest.h
while IFS= read -r line; do
    if [[ $line == *"//ECT_NO_MERGE"* ]]; then
        echo $line >> ./build/ectest.h
    elif [[ $line == *"#include"* ]]; then
        filename=$(echo $line | grep -Po '(?<=<)(.*?)(?=>)')
        cat ./include/$filename >> ./build/ectest.h
    fi
done < "$input"
echo "#endif /*ECTEST_H__*/" >> ./build/ectest.h
echo "" >> ./build/ectest.h
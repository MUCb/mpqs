#!/bin/bash

prog="./qs.out"

# for j in {3..3}; do
    # for i in {3..20}; do
for j in $(seq -f "%02g" 3 20); do
    for i in $(seq -f "%02g" $j 20); do
        echo $j
        echo $i
        # echo test_results/result_$i\_$j
        $prog $j $i > test_results_01/result_$j\_$i 2>&1
    done
done
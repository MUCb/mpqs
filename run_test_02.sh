#!/bin/bash

prog="./qs.out"

# for j in {3..3}; do
    # for i in {3..20}; do
for j in $(seq -f "%02g" 21 40); do
    for i in $(seq -f "%02g" 3 40); do
        $prog $j $i > test_results_02/result_$j\_$i 2>&1
    done
done
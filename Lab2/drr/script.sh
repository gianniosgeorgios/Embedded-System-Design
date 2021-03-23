#!/bin/bash

declare -a arr=("drr_sll_sll" "drr_sll_dll" "drr_sll_dynarr" "drr_dll_sll"
"drr_dll_dll" "drr_dll_dynarr" "drr_dynarr_sll" "drr_dynarr_dll" "drr_dynarr_dynarr")

for executable in "${arr[@]}"
do
    valgrind --log-file="mem_accesses_log.txt" --tool=lackey --trace-mem=yes ./"$executable"
    echo "$executable" >> memory_accesses.txt
    cat mem_accesses_log.txt | grep 'I\|L' | wc -l >> memory_accesses.txt
    valgrind --tool=massif ./"$executable"
    ms_print massif.out.* >> memory_footprint.txt
    rm mem_accesses_log.txt
    rm massif.out.*
done

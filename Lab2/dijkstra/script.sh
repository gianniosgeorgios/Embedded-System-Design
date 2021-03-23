#!/bin/bash

valgrind --log-file="mem_accesses_log.txt" --tool=lackey --trace-mem=yes ./dijkstra_opt_sll input.dat
echo "$executable" >> memory_accesses.txt
cat mem_accesses_log.txt | grep 'I\|L' | wc -l >> memory_accesses.txt
valgrind --tool=massif ./dijkstra_opt_sll input.dat
ms_print massif.out.* >> memory_footprint.txt
rm mem_accesses_log.txt
rm massif.out.*

valgrind --log-file="mem_accesses_log.txt" --tool=lackey --trace-mem=yes ./dijkstra_opt_dll input.dat
echo "$executable" >> memory_accesses.txt
cat mem_accesses_log.txt | grep 'I\|L' | wc -l >> memory_accesses.txt
valgrind --tool=massif ./dijkstra_opt_dll input.dat
ms_print massif.out.* >> memory_footprint.txt
rm mem_accesses_log.txt
rm massif.out.*

valgrind --log-file="mem_accesses_log.txt" --tool=lackey --trace-mem=yes ./dijkstra_opt_dynarr input.dat
echo "$executable" >> memory_accesses.txt
cat mem_accesses_log.txt | grep 'I\|L' | wc -l >> memory_accesses.txt
valgrind --tool=massif ./dijkstra_opt_dynarr input.dat
ms_print massif.out.* >> memory_footprint.txt
rm mem_accesses_log.txt
rm massif.out.*

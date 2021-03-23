# Dynamic Data Type Refinement

## Description
The purpose of the exercise is to optimize the dynamic data structures of two network applications, using the methodology "Dynamic Data Type Refinement" (DDTR). 
* The **Deficit Round Robin** (DRR) 
* The **Dijkstra** algorithm, 

 The dynamics structures of DRR and Dijkstra algorithms will be optimized over:
 * The **memory accesses**: Refers to any read and write operation by and to the main memory.
 * The **memory footprint**: Refers to the amount of main memory that a program uses or references while running.

 We use the following tools for the evaluation of data structures:
 * DDTR library
 * Massif tool of Valgrind suite
 * Lackey tool of Valgrind suite

## DRR
We run the application with all the different combinations of data structures for the list of packets and the list of nodes.
* Single Linked List (SLL)
* Double Linked List (DLL)
* Dynamic Array (DYN_ARR)

For each combination, we note its results on the memory accesses and the memory footprint. We find the **Pareto Optimal** Solutions.
<img src="https://user-images.githubusercontent.com/50949470/111882713-b72ef980-89bf-11eb-838f-9e88d2b739ef.png" width="400" height=auto>

## Dijkstra
The dijkstra algorithm finds the shortest path in a table of size 100x100. The nodes are stored in one list. We applied the DDTR methodology for this application. After we inserted the library in the application, we replaced its data structure, with the data structures of the DDTR library. The full steps are presented in the [report](https://github.com/chrisbetze/Embedded-System-Design/blob/91a22a26b7c050c0189c8f9789ee26b26646fb72/Lab2/report.pdf).

We run the application with all the different combinations of data structures.
* Single Linked List (SLL)
* Double Linked List (DLL)
* Dynamic Array (DYN_ARR)

For each combination, we note its results on the memory accesses and the memory footprint. We find the **Pareto Optimal** Solution.
<img src="https://user-images.githubusercontent.com/50949470/111882965-2527f080-89c1-11eb-91b4-c1fab6a310b9.png" width="400" height=auto>

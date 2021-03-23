# Part 1: Loop Transformations - Design Space Exploration

## Description
In this section we analyze the **Parallel Hierarchical One Dimensional Search** algorithm (PHODS), an algorithm that belongs to the domain of multimedia. The PHODS algorithm is a Motion Estimation algorithm, which aims to detect the movement of objects between two consecutive images (frame) of a video.

## Optimizations
The goal of loop transformations are:
* Improve data reuse and data locality
* Efficient use of memory hierarchy
* Reducing overheads associated with executing loops
* Instructions pipeline
* Maximize parallelism

We apply the following transformations to the code to **reduce time execution**.
* Loop fusion (merge): Combines two adjacent isomorphic loops
* Loop Unrolling: Aggregates consecutive steps of the loop and writes them explicitely (without loop constrols)
* Data Reuse

## Design Space Exploration
* In the optimized code, we apply Design Space Exploration, considering a square block of **dimensions Β**, in order to find the optimal size block B.
* In the optimized code, we apply Design Space Exploration, considering a rectangular block of **dimensions Βx-By**, in order to find the optimal size block Bx-By.

## Results
We display the results of previous tasks in one **boxplot** diagram and we compare-analyze the experimental results that we receive. All execution time calculations are performed with `python scripts`.<br>
<img src="https://user-images.githubusercontent.com/50949470/111881616-eb9fb700-89b9-11eb-82d4-efa9826b588b.png" width="600" height=auto>

# Part 2: Automated Code Optimization
## Orio Tool
[Orio](https://brnorris03.github.io/Orio/) is a Python framework for transformation and automatically tuning the performance of codes written in different source and target languages.

## Code Optimization
We use Orio tool to optimize `tables.c` code, of which the function involves simple accesses and operations with tables. For each of the following algorithms, we perform Design Space Exploration to find the optimal loop **unrolling factor**.
* Exhaustive
* Randomsearch
* Simplex

## Results
For the final optimal code, we calculate the execution times (also with python scripts) and we compare them with their initial.
|  | Minimum (s) | Average (s) | Maximum (s) | 
| ------------- | ------------- | ------------- | ------------- |
| **Exhaustive**  |  0.042233  |  0.043519  | 0.046476  |
| **Randomsearch**  |  0.042779  |  0.043983  | 0.048376  |
| **Simplex**  | 0.042181  | 0.043321  | 0.047977  |


# Advent of Code 2021

This year I solved the problems in notebooks (Jupyter, Pluto.jl), and integrated the capabilities of fetching inputs and submitting answers. The code can be found in the following directories of the repo [lucifer1004/AoC](https://github.com/lucifer1004/AoC).

- [Python](https://github.com/lucifer1004/AoC/tree/main/2021)
- [Kotlin](https://github.com/lucifer1004/AoC/tree/main/2021/kotlin)
- [Julia](https://github.com/lucifer1004/AoC/tree/main/2021/julia)

## Day01 

- Simulation.

## Day02

- Simulation.

## Day03

- Simulation.

## Day04

- Brute force, check each matrix iteratively.
- Precalculate the index of every number to determine the winning index of each matrix.

## Day05

- Simulation.

## Day06

- Dynamic programming. Can be further optimized via matrix exponentiation.

## Day07

- Enumerate all integers within the range of $[\min,\max]$ to find the minimum of the total cost function.
- Better
  - Part 1: The minimum can be obtained at the median.
  - Part 2: The total cost function is a quadratic function within each segment. The coefficients of the quadratic function can be recalculated in $\mathcal{O}(1)$ time when moving from one segment to the next.

## Day08

- Analysis. 1, 4, 7 and 8 can be determined easily. The rest digits can be determined from the intersection of each digit with the known digits. 

## Day09

- Part 1: enumeration.
- Part 2: BFS/DFS.

## Day10

- Stack.

## Day11

- BFS.

## Day12

- DFS.

## Day13

- Simulation.

## Day14

- Dynamic programming on word pairs, regardless of the sequence. The beginning and ending positions should be handled with care.

## Day15

- Shortest path via Dijkstra.

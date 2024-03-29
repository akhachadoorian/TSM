# Traveling Salesman Project 1 

## Table of Contents:
* [Overview](#overview)
* [Setup](#setup)
* [Algorithms](#algorithms)
    * [Brute Force Algorithm](#brute-force-algorithm)
    * [Nearest Neighbor Algorithm](#nearest-neighbor-algorithm)
    * [Original Algorithm](#original-algorithm)
* [Sources](#sources) 

## Overview
    This C++ code consists of three different algorithms that solve the Traveling Salesman problem. These algorithms include a Brute Force Algorithm, a Nearest Neighbor Algorithm, and an original algorithm. These algorithms are implemented in a single file where the desired algorithm or algorithms can be selected for execution.I made a few assumptions: nodes are labeled in numarical order starting at 0, no nodes were named the same, and that the graph was undirected and complete.

## Setup
    To use my C++ file, two variables must be specified at the start of the file. 
        * The first variable is a string that holds the input file name for the triangle matrix, and the second variable is an enumerated variable used to specify the algorithm or algorithms. 
        * The enumerated variable can be set to “all” (meaning all algorithms calculated), brute (only brute force method calculated), “neighbor” (only nearest neighbor algorithm used), “mine” (only my swapping implementaFon is used), and “neighborMine” (to calculate using the nearest neighbor and my implementaFon). 
    
    For the input file to be read correctly, it must have the triangular matrix with no addiFonal whitespace at the end of the file.

    Compile: g++ TSM_AK.cpp

## Algorithms

### Brute Force Algorithm
    The bruteForce function is the implementation of the Brute Force Algorithm in the code. It solves the TSM problem by finding every possible path and determining the shortest one. 

    The bruteForce function has two parameters: the two-dimensional vector holding the augmented matrix and a reference to a vector that will be filled with the shortest path. The function returns an integer value that is the cost of the shortest path. 

    The function starts by creating a local vector to hold the various paths that will be tested, and it's filled initially to have the nodes in numerical order, excluding the starting node and end node (both of which are zero). Next, two variables are initialized to hold the minimum cost and whether a permutation has occurred to know if we need to set the minimum cost and minimum path. Using a do-while loop, the current path is traveled to calculate the total cost for all permutations of the path. If this is the first permutation, the cost is stored in the minimum cost variable, and the reference vector is updated to hold the path. If the newly calculated cost is less than the minimum cost, the minimum cost variable is set to this cost, and the path is copied to the parameter vector. Otherwise, nothing is changed, and the do-while loop continues until all permutations have occurred. Once the while loop is exited, the minimum cost variable is returned. 

### Nearest Neighbor Algorithm

### Original Algorithm

## Sources

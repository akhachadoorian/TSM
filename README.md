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
    The nearestNeighbor function is the implementation of the Nearest Neighbor Algorithm in the code. It solves the problem by creating the shortest path by adding nodes with the shortest distance from the current node and that node has not been visisted yet.

    The function has six parameters, which are a two-dimensional vector holding the augmented matrix, a reference to a vector that will be set to the shortest path, an array that contains whether a node has been visited or not, the current node, the current cost, and the total number of nodes.The nearestNeighbor function will return the cost of the path. 
    
    The nearestNeighbor function begins by setting up a variable that holds the smallest distance and is set to the largest value that an integer can have (2,147,483,647). Also, a variable is initialized to contain the next node to be added to the path. Then, the array that holds whether a node has been visited (0 means it has not, and 1 means it has) has a value indexed at the current node set to 1, and the current node is added to the path. Next, the function loops through the current node’s row in the augmented matrix to find a node that has not been visited with a cost less than the current minimum cost. The minimum cost is updated if a value is found, and the next node variable is set. Once that loop is completed, the total cost variable is updated depending on the two cases. Suppose the minimum cost variable has something besides the starting value. In that case, the minimum cost variable is added to the cost variable, and the function recursively calls again, with the current node being the value in the next node variable. Otherwise, the distance from the current node to the starting node is added to the cost, and the path is updated to include the ending node. This is the base case, so the function is returned. 

### Original Algorithm
#### The Idea Behind the Algorithm
#### The Code Implementation
## Sources

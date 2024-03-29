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
##### To use my C++ file, two variables must be specified at the start of the file. 
    string fileName = 'filename.txt'
    method calcMethod = emunMethod

The first variable is a string that holds the input file name for the triangle matrix, and the second variable is an enumerated variable used to specify the algorithm or algorithms. 
The enumerated variable can be set to “all” (meaning all algorithms calculated), brute (only brute force method calculated), “neighbor” (only nearest neighbor algorithm used), “mine” (only my swapping implementaFon is used), and “neighborMine” (to calculate using the nearest neighbor and my implementaFon). 

##### For the input file to be read correctly, it must have the triangular matrix with no addiFonal whitespace at the end of the file.
##### Compile: 
    g++ TSM_AK.cpp

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
The concept behind my algorithm started with the idea of swapping nodes within the path instead of creating every possible path like the brute solution. I understood that I needed to figure out how to test if switching would affect the path's total cost before swapping the nodes to prevent my algorithm from becoming the brute-force solution. After doing some drawings, I discovered that swapping two nodes affected two connections per node (see figure 1). In other words, four edges were affected by switching two nodes. With this observation, I calculated the total distance of the current path and the total distance after the swap by adding those four connections for each path. Using the previous image path, the current distance could be calculated by adding the distances from b to f, f to d, e to c, and c to g. Using the previous image path after the swap, the new distance can be calculated by adding the distances from b to c, c to d, e to f, and f to g. Knowing what edges were affected by the swap, I created general formulas for the distance calculations. For before the swap, the equation is: Current Distance = distance(swap1PrevNode ->swapNode1) + distance(swapNode1-> swapNode1Next) + distance(swapNode2->swapNode2Next) + distance(swap2PrevNode-> swapNode2). For after the swap, the equation is: New Distance = distance(swap1PrevNode->swapNode2) + distance(swapNode2->swapNode1Next) + distance(swap2PrevNode ->swapNode1) + distance(swapNode1->swapNode2Next). I then realized that I could subtract the current distance from the new distance to find the change in distance (referred to as delta d (Δd) in my code) and determine whether the swap should happen. If the change in distance is a positive number, we know that the new distance is larger than the current distance; therefore, the swap should not happen. If the change in distance is negative, we know that the new distance is smaller than the current distance; therefore, the swap should occur. With all this, I now had a basis for my algorithm that would apply this idea of swapping variables when the change in distance is negative for all parts of the path except the start and end, in the path. I implemented this idea within my code within the findPathViaSwapping, recursiveSwapping, findNumChanges, findAndSwap, and totalCost functions.

#### The Code Implementation
The findPathViaSwapping, recursiveSwapping, findNumChanges, findAndSwap, and totalCosts functions implement my orginal solution.

##### findPathViaSwapping
The findPathViaSwapping function is the central part of my algorithm.

The function has 3 parameters: a two-dimensional vector holding the augmented matrix, a reference to a vector, and the total number of nodes. 
The function returns the path's cost and updates the referenced vector to hold the shortest path. 

The findPathViaSwapping function starts by filling 3 vectors, 2 local and the parameter vectors, with nodes in numerical order. Then, variables to hold the current and minimum costs are set up. Using the findNumChanges function, the number of swaps that result in a negative change in distance, with zero being the current node, is found, so we know how many loops need to occur to test all the swaps. Within this loop, the path vector is reset to try a new swap, and the findAndSwap function is called to apply the swap associated with the loop number (ex: if loop = 2, it applies the swap that is found after 2 possible negative changes in distance). Once the swap has occurred, the total cost is calculated using the totalCost function. This cost is compared against the stored minimum cost, and if the minimum cost is greater than the new cost, the minimum cost and minimum path are updated to the current cost and path. Then, the recursiveSwapping function is called to repeat a similar process with the remaining path nodes. Once the loop is exited, the path vector is cleared and updated to hold the minimum path. The minimum cost associated with this path is returned. 

##### recursiveSwapping
The recursiveSwapping function has five parameters: a two-dimensional vector holding the augmented matrix, a reference to a path within a vector, the current node, a reference to the minimum path, and a pointer to the minimum cost.

The function does not return any values; instead, the minimum path and minimum cost variables are updated during the execution. 

The recursiveSwapping function applies a process similar to the findPathViaSwapping function but with nodes other than the starting node. The function starts by finding the number of possible changes at the current node. A loop is then implemented to occur until the number of potential changes is reached. Within the loop, the swap occurs using the findAndSwap function, and the new cost is calculated using the totalCost function. This new cost is compared against the minimum cost, and if the minimum cost is greater than the new cost, the minimum cost and minimum path are updated. Once the loop is exited, the current node value is incremented, and if there are still more changes that can occur, the function is recursively called again for the new current node. Otherwise, the function is returned. 

##### findNumChanges
The findNumChanges function has three parameters: a two-dimensional vector holding the augmented matrix, a path vector, and the current node. 

The function returns a integer respresenting the number of possible changes that result in a negative change in distance.

The function starts by setting up a counter. The findNumChanges function then loops through all the nodes in the path that can be swapped (which is the path size minus 2). In this loop, the distance change is calculated by subtracting the current distance from the new distance. The current and new distances were computed using the general formulas discussed previously. If the subtraction results in a negative value, the counter is incremented. Once the loop has been completed, the counter variable is returned. 

##### findAndSwap
The findAndSwap function has the augmented matrix, a reference to the path vector, the current node, and a number representing which swap as parameters. 
The function does not return a value. Instead, it updates the path vector that was passed as a parameter. 

The findAndSwap function starts by setting up a counter to count the number of negative changes in distances to ensure the correct swap occurs. Then, the function loops through all swappable nodes (path size minus 2) while calculating the change in distance using the same formulas as the findNumOfChanges function. If a negative change in distance is found, it must be checked to confirm it's the correct swap by comparing it to the value passed in as a parameter. If it is not the right swap, the counter is incremented. Otherwise, the values are swapped within the path vector, and the function returns. 

##### totalCosts
The totalCost function takes two parameters: an augmented matrix within a two-dimensional vector and a vector holding a path.

This function returns an integer value represent the cost of the path.

The function uses a loop to travel the path while adding the cost of traveling from the current node to the concurrent node. 
Once the entire route has been traversed, the distance is returned.  

## Sources
[Brute Force Algorithm Reference](https://www.guru99.com/travelling-salesman-problem.html)
[Nearest Neighbor Algorithm Reference](https://www.tutorialspoint.com/design_and_analysis_of_algorithms/design_and_analysis_of_algorithms_travelling_salesman_problem.htm)
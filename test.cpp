//Alex Khachadoorian
//CS 470
//Traveling Salesman Problem

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <random>
#include <iterator> 

using namespace std;

//Assumptions:
//No duplicately named nodes
//Assume undirected/same cost either direction
//Assume that there is no negative distance
//Assume user has txt file with first line having number of nodes space starting node followed by a matrix of distances/weights
// ./a.out  distances.txt 

enum method { all, brute, neighbor, mine, neighborMine};

//global variables
string fileName = "graph.txt"; //specify the input filename
method calcMethod = neighborMine; //specify type of calculation method

//functions
void completeMatrix(vector<int> matrix, vector<vector<int> > &graph, int numNodes); //converts triangular matrix to augmented matrix
int bruteForce(vector<vector<int> > &graph, vector<int> &path); //brute force solution
int nearestNeighbor(vector<vector<int> > &graph, vector<int> &path, int visited[], int currNode, int cost, int numNodes); //nearest neighbor solution
int findPathViaSwapping(vector<vector<int> > &graph, vector<int> &path, int numNodes); //my orginial solution
void recursiveSwapping(vector<vector<int> > &graph, vector<int> &path, int currNode, vector<int> &minPath, int *minCost); //my orginial solution helper function
int findNumChanges(vector<vector<int> > &graph, vector<int> &path, int currNode); //my orginial solution helper function
void findAndSwap(vector<vector<int> > &graph, vector<int> &path, int i, int loop); //my orginial solution helper function
int totalCost(vector<vector<int> > &graph, vector<int> path); //my orginial solution helper function
void print(vector<int> &path, int numNodes, int cost, double time, method m, ofstream &outFile); //print results to file

int main() {
    //open file
    ifstream inputFile;
    inputFile.open(fileName); 

    //make sure file opens correctly
    if (!inputFile) { //if unable to open file
        //print error and abort
        cout << "Error: Unable to open file" << endl;
        return 0;
    }

    //get values for number of nodes
    int numNodes = 0;
 
    //get distance between nodes in graph
    vector<int> diagonalMatrix;
    
    while (!inputFile.eof()) { //read into variables until end of file
        //get value from file
        int temp; //temp variable to hold data from textfile
        inputFile >> temp; //load value into temp integer

        //store in vector
        diagonalMatrix.push_back(temp);

        if (temp == 0) { //if end of the row reached
            numNodes++; //increase number of nodes
        }
    }

    //close file when finished
    inputFile.close();

    //convert to normal matrix
    vector<vector<int> > graph(numNodes); //2-d vector to hold augemented matrix
    completeMatrix(diagonalMatrix, graph, numNodes); 

    //determine which methods to call
    if (calcMethod == brute) {
        //set up variables
        vector<int> path; //holds shortest path from starting node to starting node (node names not indexes)
        int cost; //shortest total distance between nodes    
        
        //call function 
        chrono::steady_clock::time_point begin = chrono::steady_clock::now(); //recond start time
        cost = bruteForce(graph, path); 
        chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); //record end time

        //determine time
        auto duration = chrono::duration_cast<std::chrono:: microseconds>(end - begin); //determine elasped time
        double time = duration.count();

        //open outfile
        ofstream outFile;
        outFile.open("tsmSolution.txt");

        //output path and total distance
        print(path, numNodes, cost, time, calcMethod, outFile);

        //close outfile
        outFile.close();
    }
    else if (calcMethod == neighbor) {
        //set up variables
        vector<int> path; //holds shortest path from starting node to starting node (node names not indexes)
        int cost = 0; //shortest total distance between nodes 
        int visited[numNodes]; //holds whether the node has been visited in path yet (1 = visited and 0 = not visited)
        
        //set up visited array to be 0 for all nodes
        for (int i = 0; i < numNodes; i++) {
            visited[i] = 0;
        }

        //call function 
        chrono::steady_clock::time_point begin = chrono::steady_clock::now(); //record start time
        cost = nearestNeighbor(graph, path, visited, 0, cost, numNodes);
        chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); //recond end time

        //determine time
        auto duration = chrono::duration_cast<std::chrono::microseconds>(end - begin);
        double time = duration.count();

        //open outfile
        ofstream outFile;
        outFile.open("tsmSolution.txt");

        //output path and total distance
        print(path, numNodes, cost, time, calcMethod, outFile);

        //close outfile
        outFile.close();
    }
    else if (calcMethod == mine) {
        //set up path
        vector<int> path;

        //call function
        chrono::steady_clock::time_point begin = chrono::steady_clock::now(); //record start time
        int cost = findPathViaSwapping(graph, path, numNodes);
        chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); //record end time

        //determine time
        auto duration = chrono::duration_cast<std::chrono:: microseconds>(end - begin); //calculate elasped time
        double time = duration.count();

        //open outfile
        ofstream outFile;
        outFile.open("tsmSolution.txt");

        //output path and total distance
        print(path, numNodes, cost, time, calcMethod, outFile);

        outFile.close();
    }
    else if (calcMethod == all) {
        //calculate using brute method
        method m = brute;

        //set up variables
        vector<int> path; //holds shortest path from starting node to starting node (node names not indexes)
        int cost; //shortest total distance between nodes 

        //call function 
        chrono::steady_clock::time_point begin = chrono::steady_clock::now(); //record start time
        cost = bruteForce(graph, path); 
        chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); //record end time

        //determine time
        auto duration = chrono::duration_cast<std::chrono:: microseconds>(end - begin); //calculate elasped time
        double time = duration.count();

        //open output
        ofstream outFile;
        outFile.open("tsmSolution.txt");

        //output path and total distance
        print(path, numNodes, cost, time, m, outFile);

        //calculate using nearest neighbor method
        m = neighbor;

        //set up variables
        path.clear();
        cost = 0; //shortest total distance between nodes 
        int visited[numNodes];
    
        //set up visited array to be 0 for not visited and 1 for visited
        for (int i = 0; i < numNodes; i++) {
            visited[i] = 0;
        }

        //call function 
        begin = chrono::steady_clock::now(); //record start time
        cost = nearestNeighbor(graph, path, visited, 0, cost, numNodes);
        end = std::chrono::steady_clock::now(); //recond end time

        //determine time
        duration = chrono::duration_cast<std::chrono::microseconds>(end - begin); //calculate elasped time
        time = duration.count();

        //output path and total distance
        print(path, numNodes, cost, time, m, outFile);

        //calculate using my swapping method
        m = mine;

        //set up path
        path.clear();

        //call function
        begin = chrono::steady_clock::now(); //record start time
        cost = findPathViaSwapping(graph, path, numNodes);
        end = std::chrono::steady_clock::now(); //recond end time

        //determine time
        duration = chrono::duration_cast<std::chrono:: microseconds>(end - begin); //calculate elasped time
        time = duration.count();

        //output path and total distance
        print(path, numNodes, cost, time, m, outFile);

        //close outfile
        outFile.close();
    }
    else if (calcMethod == neighborMine) {
        //calculate using nearest neighbor method
        method m = neighbor;

        //set up variables
        vector<int> path; //holds shortest path from starting node to starting node (node names not indexes)
        int cost; //shortest total distance between nodes 
        int visited[numNodes];
    
        //set up visited array to be 0 for not visited and 1 for visited
        for (int i = 0; i < numNodes; i++) {
            visited[i] = 0;
        }

        //call function 
        chrono::steady_clock::time_point begin = chrono::steady_clock::now(); //record start time
        cost = nearestNeighbor(graph, path, visited, 0, 0, numNodes);
        chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); //recond end time

        //determine time
        auto duration = chrono::duration_cast<std::chrono:: microseconds>(end - begin); //calculate elasped time
        double time = duration.count();

        //open output
        ofstream outFile;
        outFile.open("tsmSolution.txt");

        //output path and total distance
        print(path, numNodes, cost, time, m, outFile);

        //calculate using my swapping method
        m = mine;

        //set up path
        vector<int> path1(numNodes - 1);

        //call function
        begin = chrono::steady_clock::now(); //record start time
        cost = findPathViaSwapping(graph, path1, numNodes);
        end = std::chrono::steady_clock::now(); //recond end time

        //determine time
        duration = chrono::duration_cast<std::chrono::microseconds>(end - begin); //calculate elasped time
        time = duration.count();

        //output path and total distance
        print(path, numNodes, cost, time, m, outFile);

        //close outfile
        outFile.close();
    }
    
    return 0;

}

void completeMatrix(vector<int> matrix, vector<vector<int> > &graph, int numNodes) {
    //set up row and column counters/indexes
    int mIndex = 0; //for matrix
    int gRow = 0; //for graph
    int gCol = 0; //for graph

    //copy/convert input to diagonal matrix
    while (gRow < numNodes) { 
        //just copy values
        graph[gRow].push_back(matrix[mIndex]);

        //increase column counter
        gCol++;
        
        if (matrix[mIndex] == 0) { //if matrix's value is 0
            gRow++; //move to the next row in 2-d vector
        }

        //increase matrix counter
        mIndex++;
    }

    //reset counters
    gCol = 0;
    gRow = 0;

    //fill reset of matrix
    //copy/convert matrix to full matrix
    while (gRow < numNodes) { 
        if (graph[gRow][gCol] == 0) { //if matrix's value is 0
           //move to next value
           gCol++;

           //find values to fill remainder of row
            while (gCol < numNodes) {
                graph[gRow].push_back(graph[gCol][gRow]); //reverse the row and column in matrix for find corresponding matrix values
                gCol++;
            }

            //increase row counters and reset column counter
            gRow++;
            gCol = 0;
        }
        else {
            //move to next value
            gCol++;
        }
    }
}

int bruteForce(vector<vector<int> > &graph, vector<int> &path) { //path is passed in as a reference to allow it to be edited in function
    //set up vector to list nodes not including the starting/ending nodde
    vector<int> possiblePath; //holds indexes of nodes excluding starting node

    //create 1st path not including start and end
    for (int i = 1; i < graph.size(); i++) {
        possiblePath.push_back(i);
    }

    //set up variables
    int minCost; //variable to hold the shortest total distance (set to highest possible distance between) //FIX ME
    bool firstTime = true; //lets us know if minCost and minPath need to be set

    //determine the total cost for every combination and compare with current smallest cost
    do { //do these action while there are possible permutations
        int currCost = 0; //holds the current cost
        int currNode = 0; //holds the current node index

        //travel the path to determine the total cost
        for (int i = 0; i < possiblePath.size(); i++) {
            //add cost of traveling from the current node to node next in the path
            currCost += graph[currNode][possiblePath[i]]; 

            if ((currCost > minCost) && (firstTime == false)) {
                break;
            }

            //update current node value to next node
            currNode = possiblePath[i]; 
        }
        
        //add the distance from the last node in the path to travel to the start node
        currCost += graph[currNode][0]; //add distance to start

        //determine if a new shortest path has been found    
        if (firstTime == true) { //minCost and minPath have not been set
            //update the current min cost value to the current cost
            minCost = currCost;

            //copy path over (this updates the vector in our main())
            path.push_back(0); //add starting vector to path 

            for (int i = 0; i < possiblePath.size(); i++) {
                //copy the value from possiblePath to path
                path.push_back(possiblePath.at(i));
            }

            path.push_back(0); //add starting vector to end path 

            //update boolean variable
            firstTime = false; //now our minCost and minPath are set
        }
        else if (currCost < minCost) { //if the current total cost is less the current min cost
            //update the current min cost value to the current cost
            minCost = currCost;

            //copy path over (this updates the vector in our main())
            path.clear(); //clear the current vector
            path.push_back(0); //add starting vector to path

            for (int i = 0; i < possiblePath.size(); i++) {
                //copy the value from possiblePath to path 
                path.push_back(possiblePath.at(i));
            }

            path.push_back(0); ////add starting vector to end path
        }
    } while(next_permutation(possiblePath.begin(), possiblePath.end())); //find next permutation

    return minCost; //return the smallest minCost
}

int nearestNeighbor(vector<vector<int> > &graph, vector<int> &path, int visited[], int currNode, int cost, int numNodes) {
   //set up variables
    int minCost = 2147483647; //will hold the cost for the travel
    int nextNode; //will hold the next node in path

    //add current node to list and mark
    visited[currNode] = 1; //mark current node as visited
    path.push_back(currNode); //add node to path

    //search through current row in matrix to find smallest distance to a node that has not been visited
    for (int i = 0; i < graph.size(); i++) {
        if (graph.at(currNode).at(i) != 0 && (visited[i] != 1)) { //if node has not be visited and is not current node
            if (minCost > graph.at(currNode).at(i)) {
                minCost = graph.at(currNode).at(i); //set new min cost
                nextNode = i; //update nextNode to be this node
            }
        }
    }

    //determine if end of path and effect cost
    if (minCost != 2147483647) { //if more nodes to be visited
        cost = cost + minCost; //update cost
    }
    else { //if visited all nodes
        cost = cost + graph.at(currNode).at(0); //update cost back to starting node
        path.push_back(0); //add starting node to end of path

        return cost;
    }

    //recursively call function while updating cost
    return nearestNeighbor(graph, path, visited, nextNode, cost, numNodes);
}

int findPathViaSwapping(vector<vector<int> > &graph, vector<int> &path, int numNodes) {
    //set up path and minPath
    vector<int> minPath; //holds shortest path
    vector<int> resetPath; //holds path being used to reset path for function

    //create starting path with nodes in numerical order
    iota(path.begin(), path.end(), 1);
    // iota(minPath.begin(), minPath.end(), 0);
    // iota(resetPath.begin(), resetPath.end(), 0);

    
    shuffle(path.begin(), path.end(), random_device());
    //add ending node
    path.insert(path.begin(), 0);
    path.push_back(0);
    // minPath.push_back(0);
    // resetPath.push_back(0);

    minPath.assign(path.begin(), path.end()); 
    resetPath.assign(path.begin(), path.end()); 

    //set up costs
    int minCost = totalCost(graph, path); //will hold smallest cost
    int cost; //holds current cost   

    //determine how many possible neg distance changes when swapping next node
    int numChanges = findNumChanges(graph, path, 0); 

    for (int loop = 0; loop < numChanges; loop++) { //find swaps and apply them and find shortest one
        //reset path to not include the last swap of nextNode
        path.clear();
        for (int q = 0; q < resetPath.size(); q++) {
            path.push_back(resetPath.at(q));
        }
        
        //call function to find & swap node
        findAndSwap(graph, path, 0, loop); //swaps node in path after 0 with the node resulting in the loop# negative distance change

        //determine the cost of the current path
        cost = totalCost(graph, path);

        //check if new cost smaller than minCost
        if (cost < minCost) {
            //update min path
            minPath.clear();
            for (int q = 0; q < path.size(); q++) {
                minPath.push_back(path.at(q));
            } 

            //update cost
            minCost = cost;
        }

        //call function to try with remaining nodes
        recursiveSwapping(graph, path, 1, minPath, &minCost);
    }

    //make path the minPath before return
    path.clear();
    for (int q = 0; q < minPath.size(); q++) {
        path.push_back(minPath.at(q));
    }

    return minCost; //returns the cost of the minimum path
}

void recursiveSwapping(vector<vector<int> > &graph, vector<int> &path, int currNode, vector<int> &minPath, int *minCost) {
    //determine how many possible neg distance changes when swapping next node
    int numChanges = findNumChanges(graph, path, currNode); 

    for (int loop = 0; loop < numChanges; loop++) { //find swaps and apply them and find shortest one
        //call function to find & swap node
        findAndSwap(graph, path, currNode, loop); //swaps node in path after the current node with the node resulting in the loop#th negative distance change

        //find cost of the current path
        int cost = totalCost(graph, path);

        //check if new cost smaller than minCost
        if (cost < *minCost) {
            //update min path
            minPath.clear();
            for (int q = 0; q < path.size(); q++) {
                minPath.push_back(path.at(q));
            } 

            //update cost
            *minCost = cost;
        }
    }

    //move to next node in path
    currNode++;

    if (currNode < path.size() - 2) { //if more nodes can be swap
        recursiveSwapping(graph, path, currNode, minPath, minCost); //apply function for next node in the path
        cout << ".";
    }
    else { //no more swappable nodes
        return;
    }
}

int findNumChanges(vector<vector<int> > &graph, vector<int> &path, int currNode) {
    //setup counter
    int negDeltaCounter = 0; //counts the number of swaps that result in a negative change in distance
    int i = currNode; 

    //determine how many swaps could decrease distance
    for (int j = i + 1; j < path.size() - 2; j++) {
        //calculate delta d
        int currDist = graph[path.at(i)][path.at(i + 1)] + graph[path.at(j)][path.at(j + 1)] + graph[path.at(i + 1)][path.at(i + 2)] + graph[path.at(j)][path.at(j - 1)];
        int newDist = graph[path.at(i + 1)][path.at(j + 1)] + graph[path.at(i)][path.at(j)] + graph[path.at(j)][path.at(i + 2)] + graph[path.at(j - 1)][path.at(i + 1)];
        int deltaD = newDist - currDist;

        //if change in distance negative increment counter
        if (deltaD < 0) {
            negDeltaCounter++;
        }
    }

    return negDeltaCounter; //return the number of negative changes found
}

void findAndSwap(vector<vector<int> > &graph, vector<int> &path, int i, int loop) {
    //set up counter 
    int deltaCounter = 0; //holds the number of negative changes in distance found
    
    //find and swap nextNode
    for (int j = i + 1; j <= path.size() - 2; j++) {
        //calculate delta d
        int currDist = graph[path.at(i)][path.at(i + 1)] + graph[path.at(j)][path.at(j + 1)] + graph[path.at(i + 1)][path.at(i + 2)] + graph[path.at(j)][path.at(j - 1)];
        int newDist = graph[path.at(i + 1)][path.at(j + 1)] + graph[path.at(i)][path.at(j)] + graph[path.at(j)][path.at(i + 2)] + graph[path.at(j - 1)][path.at(i + 1)];
        int deltaD = newDist - currDist;

        //if change in distance negative
        if (deltaD < 0) { 
            if (loop != deltaCounter) { //if we already tried that chanage
                deltaCounter++; //increment counter and continue
                continue;
            }
            else {
                //swap values
                swap(path.at(i+1), path.at(j));
                return;
            } 
        }   
    }
}

int totalCost(vector<vector<int> > &graph, vector<int> path) {
    //set up variables
    int cost = 0; //holds the cost of the path

    //travel path to find cost
    for (int i = 0; i < path.size() - 1; i++) {
        int currNode = path.at(i);
        int nextNode = path.at(i + 1);
        cost = cost + graph[currNode][nextNode]; //add cost of traveling from current node to the next node in path
    } 
    
    return cost; //return cost of path
}

void print(vector<int> &path, int numNodes, int cost, double time, method m, ofstream &outFile) {
    //output method
    if (m == brute) {
        outFile << "Brute Force Algorithm: " << endl;
        outFile << "----------------------" << endl;
    }
    else if (m == neighbor) {
        outFile << "Nearest Neighbor Algorithm: " << endl;
        outFile << "---------------------------" << endl;
    }
    else if (m == mine) {
        outFile << "My Swapping Algorithm: " << endl;
        outFile << "----------------------" << endl;
    }
    
    //output total distance
    outFile << "The Total Distance: ";
    outFile << cost << endl;

    //compute time
    if (time >= 1000.0) {//convert to milliseconds
        double milli = time / 1000.0; //convert to millseconds

        if (milli >= 1000.0) { //atleast a sec
            double seconds = milli / 1000.0;

            if (seconds >= 60.0) { //atleast a minute
                double minutes = seconds / 60.0;

                if (minutes >= 60.0) { //atleast an hour
                    double hours = minutes / 60.0;
                    outFile << "Running Time of Algorithm: " << hours <<  " hours" << endl;
                }
                else { //under an hour
                    outFile << "Running Time of Algorithm: " << minutes <<  " mins" << endl;
                }
            }
            else { //under a minute
                outFile << "Running Time of Algorithm: " << seconds <<  " sec" << endl;
            }
        }
        else { //less than a sec so stay as milliseconds
            outFile << "Running Time of Algorithm: " << milli <<  " ms" << endl;
        }
    }
    else { //leave as microseconds
        outFile << "Running Time of Algorithm: " << time <<  " micro sec" << endl;
    }
        

    //output shortest path
    outFile << "Shortest Path: ";
    for (int p = 0; p < path.size(); p++) {
        outFile << path.at(p) << " ";
    }
    outFile << endl << "----------------------" << endl;
}


//Brute Force Algorithm Reference: https://www.guru99.com/travelling-salesman-problem.html
//Nearest Neighbor Algorithm Reference: https://www.tutorialspoint.com/design_and_analysis_of_algorithms/design_and_analysis_of_algorithms_travelling_salesman_problem.htm

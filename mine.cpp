#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <chrono> //g++ mine.cpp -std=c++11

using namespace std;

void completeMatrix(vector<vector<int> > &matrix, vector<vector<int> > &graph, int numNodes) {
    //set up row and column counters/indexes
        int mRow = 0; //for matrix
        int mCol = 0; //for matrix
        int gRow = 0; //for graph
        int gCol = 0; //for graph
    
    //copy/convert matrix to full matrix
        while (gRow < numNodes) { 
            if (matrix[mRow][mCol] != 0) { //if matrix's value is not 0
                //just copy values
                graph[gRow].push_back(matrix[mRow][mCol]);

                //increase column counters
                gCol++;
                mCol++;
            }
            else {
                //find values to fill remainder of row
                    while (gCol < numNodes) {
                        graph[gRow].push_back(matrix[gCol][gRow]); //reverse the row and column in matrix for find corresponding matrix values
                        gCol++;
                    }

                //increase row counters and reset column counters
                mRow++;
                gRow++;
                mCol = 0;
                gCol = 0;
            }
        }
}

void findPathViaSwapping(vector<vector<int> > &graph, vector<int> &path, int numSwappable) {
    for (int i = 0; i < numSwappable; i++) {
        for (int j = i + 1; j <= numSwappable; j++) {
            //calculate delta d
            int currDist = graph[i][i + 1] + graph[j][j + 1] + graph[i + 1][i + 2] + graph[j][j - 1];
            int newDist = graph[i + 1][j + 1] + graph[i][j] + graph[j][i + 2] + graph[j - 1][i + 1];
            // int currDist = graph[i][i + 1] + graph[j][j+1];
            // int newDist = graph[i + 1][j + 1] + graph[i][j]; 
            int deltaD = newDist - currDist;

            // if (printStmt) {
            //     cout << "v1: " << i + 1 << " v2: " << j + 1 << endl;
            //     cout << "deltaD: " << deltaD << endl;


            //determine if wanna swap
            if (deltaD > 0) { //the swap would add distance
                continue;
            }
            else if (deltaD < 0) { //swapping would reduce the distance
                // if (printStmt) {
                //     cout << "Swaping nodes" << endl;
                // }

                //swap nodes
                    vector<int> newPath;
                    //copy start
                        for (int k = 0; k <= i; k++) {
                            newPath.push_back(path.at(k));
                        }
                    
                    //swap variable
                        newPath.push_back(path.at(j));

                    //copy middle
                        for (int p = i + 1; p < j; p++) {
                            newPath.push_back(path.at(p));
                        }
                    
                    //copy end
                        for (int m = j + 1; m < path.size(); m++) {
                            newPath.push_back(path.at(m));
                        }

                //copy back to path
                    path.clear();
                    for (int q = 0; q < newPath.size(); q++) {
                        path.push_back(newPath.at(q));
                    } 
                //break;
            }

        }
    }

    // if (printStmt) {
    //     cout << "-----------------------------------" << endl;
    // }
}

int totalCost(vector<vector<int> > &graph, vector<int> path) {
    int cost = 0;
    for (int i = 0; i < path.size() - 1; i++) {
        int currNode = path.at(i);
        int nextNode = path.at(i+1);
        cost = cost + graph[currNode][nextNode];
    }

    return cost;
}

void convertIndexesToNodes(vector<int> indexes, vector<int> &nodes) {
    for (int i = 0; i < indexes.size(); i++) {
        nodes.push_back(indexes.at(i) + 1);
    }
}

void print(vector<int> &path, int numNodes, int cost, int startingNode) {
    //output stating/ending node
        cout << "Starting and Ending at Node: " << startingNode << endl;

    //output shortest path
        cout << "Shortest Path: ";
        for (int p = 0; p < path.size(); p++) {
            cout << path.at(p) << " ";
        }
        cout << endl;

    //output total distance
        cout << "The Total Distance: ";
        cout << cost << endl;
}

int main() {
    //get data from file
        //open file
            ifstream inputFile;
            inputFile.open("Size100.txt"); 

        //make sure file opens correctly
            if (!inputFile) { //if unable to open file
                //print error and abort
                cout << "Error: Unable to open file" << endl;
                return 0;
            }

        //get values for number of nodes and what node is that start
            int numNodes; //holds the number of nodes
            int startingNode; //hold the index of the starting node

            inputFile >> numNodes;
            inputFile >> startingNode;
            
            startingNode--; //substract 1 so the value reflexs the index
 
    //get distance between nodes in graph
        vector<vector<int> > diagonalMatrix(numNodes); //FIX ME graph.at(node).at(otherNode) = distance from node to otherNode OR graph[node][otherNode] = distance from node to otherNode
        int row = 0; //holds row index
        int col = 0; //holds col index
        
        while (!inputFile.eof()) { //read into variables until end of file
            int temp; //temp variable to hold data from textfile

            inputFile >> temp; //load value into temp integer

            //make sure complete graph
                if ((temp == 0) && (row != col)) { //if no path to a node
                    cout << "Error: Complete graph was not entered" << endl;
                    return 0;
                }

            //put values into vector
            if (temp == 0) {
                diagonalMatrix[row].push_back(temp); //add integer into to 2-D vector
                row++;
                col = 0;
            }
            else {
                diagonalMatrix[row].push_back(temp); //add integer into to 2-D vector
                col++;
            }
        }

        vector<vector<int> > graph(numNodes);
        completeMatrix(diagonalMatrix, graph, numNodes);

    //close file when finished
        inputFile.close();

    //set up path
    
        vector<int> path;
        path.push_back(startingNode);
        for (int i = 0; i < numNodes; i++) {
            if (i != startingNode) {
                path.push_back(i); //if change to letters make it add correct thing
            }
        }
        path.push_back(startingNode);

        //determine number of swapable nodes
            int numSwappable = path.size() - 2; //subtract 2 for start and end

        //output which method
            cout << "Calculating using My Swapping Algorithm: " << endl;
            cout << "-----------------------------------" << endl;

        //call function
            int cost; //hold current cost
            int loop = 0; //loop counter
            vector<int> minPath; //holds
            int minCost;
            cost = totalCost(graph, path);
            for (int q = 0; q < path.size(); q++) {
                minPath.push_back(path.at(q));
            }
            minCost = cost;

            auto start = chrono::high_resolution_clock::now(); //starts timer

            while (loop <= 100) {
                findPathViaSwapping(graph, path, numSwappable);  //uses matrix of distances, a set path, and the number of swapable values and updates the path by swapping certain nodes

            //determine cost of path
                cost = totalCost(graph, path);
                
                if (cost < minCost) {
                    //cout << "MIN" << endl;
                    minPath.clear();
                    for (int q = 0; q < path.size(); q++) {
                            minPath.push_back(path.at(q));
                    } 
                    minCost = cost;
                }
                loop++;   
            }
            auto stop = chrono::high_resolution_clock::now(); //ends timer

        //convert path from indexes to actual nodes
            vector<int> pathNodes;
            convertIndexesToNodes(minPath, pathNodes);

        //output path and total distance
            cout << "Results For My Swapping Algorithm: " << endl;
            print(pathNodes, numNodes, minCost, startingNode + 1);
            auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
            cout << "Running Time of Algorithm: " << duration.count() <<  "ms" << endl;
            cout << "-----------------------------------" << endl << endl;

}

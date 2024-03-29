#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <random>

using namespace std;

//-std=c++11
int main() {
    int numNodes = 1000;
    int numNumbers = numNodes * (numNodes - 1) / 2;
    srand(time(NULL));
    int start = (rand() % 10) + 1;
    int end = start + numNumbers;
    vector<int> matrix(end - start);
    iota(matrix.begin(), matrix.end(), start);
    shuffle(matrix.begin(), matrix.end(), random_device());
    // shuffle(matrix.begin(), matrix.end(), random_device());
    // shuffle(matrix.begin(), matrix.end(), random_device());

    ofstream myFile;
    myFile.open("graph.txt");
    int row = 0;
    int col = 0;
    int i = 0;
    while (1) {
        if (row == col) {
            if (row == numNodes - 1) {
                myFile << 0;
                break;
            }
            else {
                myFile << 0 << endl;
                col = 0;
                row++;
            }
        }
        else {
            myFile << matrix.at(i) << " ";
            col++;
            i++;
        }
    }

    //boobs

//hi max was here
}
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;




int main(int argc, char* argv[]){

    // read command line inputs and open file
    if (argc != 3){
        cerr << "Usage: " << argv[0] << " [INPUT_FILE]" << endl;
        return 1;
    }
    string inputFileName = argv[1];
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()){
        cerr << "Couldn't open file '" << inputFileName << "'" << endl;
        return 1;
    }

    // adjacency lists
    vector<unordered_set<int>> graph, graphReverse;
    
    // read input
    int numVertices;
    inputFile >> numVertices;
    for (int i = 1; i < numVertices+1; i++){
        int numEdges, vertex;
        inputFile >> numEdges;
        for (int j = 0; j < numEdges; j++){
            inputFile >> vertex;
            // these might be backwards idk
            graph[vertex].insert(i);
            graphReverse[i].insert(vertex);
        }
    }
    inputFile.close();


    // TODO: turn graph into strongly connected components


    // TODO: run algorithm

}
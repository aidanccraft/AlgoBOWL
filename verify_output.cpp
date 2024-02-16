#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

bool DFS(int curr, vector<vector<int>> &adj, unordered_set<int> discovered, unordered_set<int> processed){
    if (processed.count(curr)) return true;
    if (discovered.count(curr)) return false;
    discovered.insert(curr);

    for (int child : adj[curr]){
        if (!DFS(child, adj, discovered, processed)) return false;
    }
    discovered.erase(curr);
    processed.insert(curr);
    return true;
}

// check if a graph is a DAG (in O(V+E) time)
bool isDAG(vector<vector<int>> adj){
    unordered_set<int> discovered, processed;

    // start DFS from every node
    for (int start = 1; start < adj.size(); start++){
        DFS(start, adj, discovered, processed);
    }
    return true;
}


int main(int argc, char* argv[]){

    // read command line inputs
    if (argc != 3){
        cerr << "Usage: " << argv[0] << " [INPUT_FILE] [OUTPUT_FILE]" << endl;
        return 1;
    }
    string inputFileName = argv[1];
    string outputFileName = argv[2];

    // open input file
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()){
        cerr << "Couldn't open file '" << inputFileName << "'" << endl;
        return 1;
    }
    // open output file
    ifstream outputFile(outputFileName);
    if (!outputFile.is_open()){
        cerr << "Couldn't open file '" << outputFileName << "'" << endl;
        return 1;
    }

    // get vertices to remove
    int numVerticesToRemove, vertex;
    outputFile >> numVerticesToRemove;
    unordered_set<int> removedVertices;
    for (int i = 0; i < numVerticesToRemove; i++){
        outputFile >> vertex;
        removedVertices.insert(vertex);
    }
    outputFile.close();

    // create graph (ignoring removed vertices)
    int numVertices;
    inputFile >> numVertices;
    vector<vector<int>> adj(numVertices+1, vector<int>());
    for (int i = 1; i < numVertices+1; i++){
        int numEdges, vertex;
        inputFile >> numEdges;
        for (int j = 0; j < numEdges; j++){
            inputFile >> vertex;
            // skip if vertex has been removed
            if (removedVertices.count(i) || removedVertices.count(vertex)) continue;
            adj[vertex].push_back(i);
        }
    }
    inputFile.close();

    // check if graph is a DAG
    if (isDAG(adj)){
        cout << "success!" << endl;
    } else {
        cout << "failed" << endl;
    }

    return 0;
}
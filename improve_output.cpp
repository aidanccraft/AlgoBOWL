#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

bool DFS(int curr, vector<unordered_set<int>>& adj, vector<char>& color) {
    if (color[curr] == 'b') return true;
    if (color[curr] == 'g') return false;

    color[curr] = 'g';

    for (int child : adj[curr]) {
        if (!DFS(child, adj, color)) return false;
    }

    color[curr] = 'b';
    return true;
}

// check if a graph is a DAG (in O(V+E) time)
bool isDAG(vector<unordered_set<int>>& adj) {
    vector<char> color(adj.size(), 'w');

    // start DFS from every node
    for (int start = 1; start < adj.size(); start++) {
        if (!DFS(start, adj, color)) return false;
    }

    return true;
}


int main(int argc, char* argv[]) {
    // read command line inputs
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " [INPUT_FILE] [OUTPUT_FILE] [NEW_OUTPUT_FILE]" << endl;
        return 1;
    }

    string inputFileName = argv[1];
    string outputFileName = argv[2];
    string newOutputFileName = argv[3];

    // open input file
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        cerr << "Couldn't open file '" << inputFileName << "'" << endl;
        return 1;
    }

    // open output file
    ifstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cerr << "Couldn't open file '" << outputFileName << "'" << endl;
        return 1;
    }

    ofstream newOutputFile(newOutputFileName);
    if (!newOutputFile.is_open()) {
        cerr << "Couldn't open file '" << newOutputFileName << "'" << endl;
        return 1;
    }

    // get vertices to remove
    int numVerticesToRemove, vertex;
    vector<int> verticesToRemove;
    outputFile >> numVerticesToRemove;
    unordered_set<int> okayVertices;

    for (int i = 0; i < numVerticesToRemove; i++) {
        outputFile >> vertex;
        verticesToRemove.push_back(vertex);
    }

    // create graph (ignoring removed vertices)
    int numVertices;
    inputFile >> numVertices;
    vector<unordered_set<int>> baseGraph(numVertices + 1, unordered_set<int>());
    for (int i = 1; i < numVertices + 1; i++) {
        int numEdges, vertex;
        inputFile >> numEdges;
        for (int j = 0; j < numEdges; j++) {
            inputFile >> vertex;
            baseGraph[i].insert(vertex);
        }
    }

    inputFile.close();
    outputFile.close();

    for (int n = 0; n < numVerticesToRemove; n++) {
        int currentVertex;
        unordered_set<int> removedVertices;

        for (int i = 0; i < numVerticesToRemove; i++) {
            if (i == n) {
                currentVertex = verticesToRemove[i];
            } else if (okayVertices.count(verticesToRemove[i])) {
                continue;
            } else {
                removedVertices.insert(verticesToRemove[i]);
            }
        }

        vector<unordered_set<int>> adj(baseGraph.begin(), baseGraph.end());

        for (int i = 1; i < adj.size(); i++) {
            if (removedVertices.count(i)) {
                adj[i] = unordered_set<int>();
            } else {
                for (int node : adj[i]) {
                    if (removedVertices.count(node)) adj[i].erase(node);
                }
            }
        }

        // check if graph is a DAG
        if (isDAG(adj)) {
            okayVertices.insert(currentVertex);
        } else {
            // cout << "failed" << endl;
        }
    }

    newOutputFile << verticesToRemove.size() - okayVertices.size() << endl;

    for (int node : verticesToRemove) {
        if (okayVertices.count(node)) continue;
        else newOutputFile << node << " ";
    }

    newOutputFile.close();

    return 0;
}
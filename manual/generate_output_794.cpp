#include <iostream>
#include <vector>
#include <deque>
#include <unordered_set>
#include <fstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <chrono>

using namespace std;

typedef unordered_map<int, unordered_set<int>> adjacency_list;


int main(int argc, char* argv[]) {
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    // read command line inputs and open files
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " [INPUT_FILE] [OUTPUT_FILE]" << endl;
        return 1;
    }

    string inputFileName = argv[1];
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        cerr << "Couldn't open file '" << inputFileName << "'" << endl;
        return 1;
    }

    string outputFileName = argv[2];
    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cerr << "Couldn't open file '" << outputFileName << "'" << endl;
        return 1;
    }

    // read input
    int numVertices;
    inputFile >> numVertices;

    // adjacency lists
    adjacency_list graph, graphReverse, doneEdges;

    for (int i = 1; i < numVertices + 1; i++) {
        graph[i] = unordered_set<int>();
        graphReverse[i] = unordered_set<int>();
        doneEdges[i] = unordered_set<int>();
    }

    for (int i = 1; i < numVertices + 1; i++) {
        int numEdges, vertex;
        inputFile >> numEdges;
        for (int j = 0; j < numEdges; j++) {
            inputFile >> vertex;
            if (vertex != i+1){
                graphReverse[vertex].insert(i);
                graph[i].insert(vertex);
            }
        }
    }
    inputFile.close();

    stack<int> starts, ends;
    vector<int> removedNodes;
    for (int i = 1; i < numVertices+1; i++) {
        for (int start : graphReverse[i]){
            starts.push(start);
            ends.push(i);
        }
        if (graph[i].size() > 0){
            removedNodes.push_back(i);
            while (!starts.empty()){
                int start = starts.top(), end = ends.top();
                starts.pop(); ends.pop();
                graph[start].erase(end);
            }
        }
    }

    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "start to finish " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 60000000.0 << "[m]" << endl;

    // create output file
    outputFile << removedNodes.size() << endl;
    for (int node : removedNodes) outputFile << node << " ";
    outputFile.close();
}

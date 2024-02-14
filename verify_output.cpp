#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

const string INPUT_FILE = "inputs/sample.txt";
const string OUTPUT_FILE = "outputs/sample1.txt";


// check if a graph is a DAG (in O(V+E) time)
bool isDAG(vector<vector<int>> adjLists){
    unordered_set<int> discovered;

    // start DFS from every node
    for (int start = 1; start < adjLists.size(); start++){
        if (discovered.count(start)) continue;
        // setup
        stack<int> stack;
        stack.push(start);
        // DFS
        int curr;
        while (!stack.empty()){
            curr = stack.top();
            stack.pop();

            if (discovered.count(curr)) return false;
            discovered.insert(start);

            for (int neighbor : adjLists[curr]){
                stack.push(neighbor);
            }
        }
    }
    return true;
}



int main(){

    // open input file
    ifstream inputFile(INPUT_FILE);
    if (!inputFile.is_open()){
        cerr << "Couldn't open file '" << INPUT_FILE << "'" << endl;
        return 1;
    }
    // open output file
    ifstream outputFile(OUTPUT_FILE);
    if (!outputFile.is_open()){
        cerr << "Couldn't open file '" << OUTPUT_FILE << "'" << endl;
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
    vector<vector<int>> adjLists(numVertices+1, vector<int>());
    for (int i = 1; i < numVertices+1; i++){
        int numEdges, vertex;
        inputFile >> numEdges;
        for (int j = 0; j < numEdges; j++){
            inputFile >> vertex;
            // skip if vertex has been removed
            if (removedVertices.count(i) || removedVertices.count(vertex)) continue;
            adjLists[vertex].push_back(i);
        }
    }
    inputFile.close();

    // check if graph is a DAG
    if (isDAG(adjLists)){
        cout << "success!" << endl;
    } else {
        cout << "failed" << endl;
    }

    return 0;
}
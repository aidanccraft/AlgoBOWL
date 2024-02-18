#include <iostream>
#include <vector>
#include <deque>
#include <unordered_set>
#include <fstream>
#include <stack>
#include <string>

using namespace std;

void sortVisit(vector<unordered_set<int>>& g, int u, vector<char>& color, deque<int>& toposort) {
    color[u] = 'g';
    for (int v : g[u]) {
        if (color[v] == 'w') {
            sortVisit(g, v, color, toposort);
        }
    }
    color[u] = 'b';
    // when a vertex has been fully processed it can be added to the front of the toposort list
    // this forces the last vertex to be processed to be the first vertex popped from toposort
    toposort.push_front(u);
}

deque<int> sortGraph(vector<unordered_set<int>>& g) {
    // perform DFS to toposort the graph
    deque<int> toposort;
    vector<char> color(g.size(), 'w');
    int numVertices = g.size();
    for (int u = 0; u < numVertices; ++u) {
        if (color[u] == 'w') {
            sortVisit(g, u, color, toposort);
        }
    }
    return toposort;
}

vector<unordered_set<int>> makeGTranspose(vector<unordered_set<int>>& g) {
    vector<unordered_set<int>> newGraph(g.size());
    for (size_t i = 0; i < g.size(); ++i) {
        for (int vertex : g[i]) {
            newGraph[vertex].insert(i);
        }
    }
    return newGraph;
}

void sccVisit(int u, vector<unordered_set<int>>& gTranspose, unordered_set<int>& scc, vector<char>& color) {
    color[u] = 'g';
    for (int v : gTranspose[u]) {
        if (color[v] == 'w') {
            scc.insert(v);
            sccVisit(v, gTranspose, scc, color);
        }
    }
    color[u] = 'b';
}

deque<unordered_set<int>> generateSccForest(deque<int>& topoSort, vector<unordered_set<int>>& gTranspose) {
    deque<unordered_set<int>> sccForest;
    vector<char> color(gTranspose.size(), 'w');
    while (!topoSort.empty()) {
        int u = topoSort.front();
        topoSort.pop_front();
        // perform DFS on gTranspose in the order of toposorted vertices
        if (color[u] == 'w') {
            unordered_set<int> scc;
            scc.insert(u);
            sccVisit(u, gTranspose, scc, color);
            if (scc.size() > 1) {
                sccForest.push_back(scc);
            }
        }
    }
    return sccForest;
}

// this is just a debugging function
void printSccForest(deque<unordered_set<int>> sccForest){
    for (int i = 0; i < sccForest.size(); i++) {
        unordered_set<int> scc = sccForest[i];
        cout << "SCC:";
        for (const auto& vertex : scc){
            cout << " " << vertex;
        }
        cout << endl;
    }
}

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

    // read input
    int numVertices;
    inputFile >> numVertices;
    
    // adjacency lists
    vector<unordered_set<int>> graph(numVertices+1), graphReverse(numVertices+1);
    
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

    // toposort the original graph
    deque<int> topoSort = sortGraph(graph);
    // I wrote a function to generate the transpose for when we test graphs after running the algorithm
    // but for the first scc generation we can use the reverse graph generated above 
    vector<unordered_set<int>> gTranspose = makeGTranspose(graph);
    // generate sccForest from the toposort and gTranspose
    deque<unordered_set<int>> sccForest = generateSccForest(topoSort, gTranspose);


    // TODO: run algorithm

}

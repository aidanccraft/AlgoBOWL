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

void sortVisit(adjacency_list& g, int u, unordered_map<int, char>& color, deque<int>& toposort) {
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

deque<int> sortGraph(adjacency_list& g) {
    // perform DFS to toposort the graph
    deque<int> toposort;
    unordered_map<int, char> color;
    for (const auto& u : g) color[u.first] = 'w';

    for (const auto& u : g) {
        if (color[u.first] == 'w') {
            sortVisit(g, u.first, color, toposort);
        }
    }

    return toposort;
}

adjacency_list makeGTranspose(adjacency_list& g) {
    adjacency_list newGraph;
    for (const auto& node : g) {
        for (int vertex : node.second) {
            newGraph[vertex].insert(node.first);
        }
    }
    return newGraph;
}

void sccVisit(int u, adjacency_list& gTranspose, unordered_set<int>& scc, unordered_map<int, char>& color) {
    color[u] = 'g';
    for (int v : gTranspose[u]) {
        if (color[v] == 'w') {
            scc.insert(v);
            sccVisit(v, gTranspose, scc, color);
        }
    }
    color[u] = 'b';
}

deque<adjacency_list> generateSccForest(deque<int>& topoSort, adjacency_list& graph, adjacency_list& gTranspose) {
    deque<adjacency_list> sccForest;
    unordered_map<int, char> color;
    for (const auto& u : gTranspose) color[u.first] = 'w';

    while (!topoSort.empty()) {
        int u = topoSort.front();
        topoSort.pop_front();
        // perform DFS on gTranspose in the order of toposorted vertices
        if (color[u] == 'w') {
            unordered_set<int> sccNodes = { u };
            sccVisit(u, gTranspose, sccNodes, color);
            adjacency_list scc;

            for (int node : sccNodes) {
                scc[node] = unordered_set<int>();
                for (int edge : graph[node]) {
                    if (sccNodes.count(edge)) scc[node].insert(edge);
                }
            }

            if (scc.size() > 1) {
                sccForest.push_back(scc);
            }
        }
    }

    return sccForest;
}

// this is just a debugging function
void printSccForest(deque<adjacency_list> sccForest) {
    for (int i = 0; i < sccForest.size(); i++) {
        adjacency_list& scc = sccForest[i];
        cout << "SCC:";
        for (const auto& vertex : scc) {
            cout << " " << vertex.first;
        }
        cout << endl;
    }
}

void heuristicVisit(int u, adjacency_list& scc, adjacency_list& sccReverse, unordered_map<int, char>& color,
    unordered_map<int, int>& weight, pair<int, int>& highestWeight) {
    color[u] = 'g';
    for (int v : scc[u]) {
        if (scc.count(v)) {
            if (color[v] == 'w') {
                weight[v] = weight[u] + sccReverse[v].size() - scc[u].size();
                if (weight[v] > highestWeight.second)
                    highestWeight = make_pair(v, weight[v]);
                heuristicVisit(v, scc, sccReverse, color, weight, highestWeight);
            }
        }
    }
    color[u] = 'b';
}

int generateHeuristic(adjacency_list& scc, adjacency_list& sccReverse) {
    unordered_map<int, char> color;
    unordered_map<int, int> weight;
    int start;

    // initialize DFS variables
    for (const auto& node : scc) {
        color[node.first] = 'w';
        weight[node.first] = 0;
        start = node.first;
    }

    // initialize start node
    weight[start] = sccReverse[start].size() - 1;
    pair<int, int> highestWeight = make_pair(start, weight[start]);

    // run DFS on SCC and assign weight to each node
    heuristicVisit(start, scc, sccReverse, color, weight, highestWeight);

    // return highest weighted node
    return highestWeight.first;
}

deque<adjacency_list> removeNode(adjacency_list& scc, adjacency_list& sccReverse, int removedNode) {
    // remove node and update graphs
    unordered_set<int> outVertices = scc[removedNode];
    unordered_set<int> inVertices = sccReverse[removedNode];

    for (int outVertex : outVertices) {
        sccReverse[outVertex].erase(removedNode);
    }

    for (int inVertex : inVertices) {
        scc[inVertex].erase(removedNode);
    }

    scc.erase(removedNode);
    sccReverse.erase(removedNode);

    // calculate sccForest from new graph
    deque<int> topoSort = sortGraph(scc);
    deque<adjacency_list> sccForest = generateSccForest(topoSort, scc, sccReverse);

    return sccForest;
}

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
    adjacency_list graph, graphReverse;

    for (int i = 1; i < numVertices + 1; i++) {
        graph[i] = unordered_set<int>();
        graphReverse[i] = unordered_set<int>();
    }

    for (int i = 1; i < numVertices + 1; i++) {
        int numEdges, vertex;
        inputFile >> numEdges;
        for (int j = 0; j < numEdges; j++) {
            inputFile >> vertex;
            graphReverse[vertex].insert(i);
            graph[i].insert(vertex);
        }
    }
    inputFile.close();

    // toposort the original graph
    deque<int> topoSort = sortGraph(graph);

    // generate sccForest
    deque<adjacency_list> sccForest = generateSccForest(topoSort, graph, graphReverse);

    vector<int> removedNodes;

    // run algorithm
    while (!sccForest.empty()) {
        adjacency_list scc = sccForest.front();
        adjacency_list sccReverse = makeGTranspose(scc);

        // get node to remove
        int nodeToRemove = generateHeuristic(scc, sccReverse);
        removedNodes.push_back(nodeToRemove);

        // remove node and create new scc forest
        deque<adjacency_list> newSccForest = removeNode(scc, sccReverse, nodeToRemove);
        sccForest.pop_front();

        // add sccs to forest
        for (adjacency_list newScc : newSccForest) sccForest.push_back(newScc);
    }

    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "start to finish " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 60000000.0 << "[m]" << endl;

    // create output file
    outputFile << removedNodes.size() << endl;
    for (int node : removedNodes) outputFile << node << " ";
    outputFile.close();
}

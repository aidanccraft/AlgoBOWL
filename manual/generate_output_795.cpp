#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef vector<int> vi;


bool dfs(int a, int L, vector<vi>& g, vi& btoa, vi& A, vi& B) {
    if (A[a] != L) return 0;
    A[a] = -1;
    for (int b : g[a]) if (B[b] == L + 1) {
        B[b] = 0;
        if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
            return btoa[b] = a, 1;
    }
    return 0;
}
int hopcroftKarp(vector<vi>& g, vi& btoa) {
    int res = 0;
    vi A(g.size()), B(btoa.size()), cur, next;
    for (;;) {
        fill(all(A), 0);
        fill(all(B), 0);
        /// Find the starting nodes for BFS (i.e. layer 0).
        cur.clear();
        for (int a : btoa) if(a != -1) A[a] = -1;
        rep(a,0,sz(g)) if(A[a] == 0) cur.push_back(a);
        /// Find all layers using bfs.
        for (int lay = 1;; lay++) {
            bool islast = 0;
            next.clear();
            for (int a : cur) for (int b : g[a]) {
                if (btoa[b] == -1) {
                    B[b] = lay;
                    islast = 1;
                }
                else if (btoa[b] != a && !B[b]) {
                    B[b] = lay;
                    next.push_back(btoa[b]);
                }
            }
            if (islast) break;
            if (next.empty()) return res;
            for (int a : next) A[a] = lay;
            cur.swap(next);
        }
        /// Use DFS to scan for augmenting paths.
        rep(a,0,sz(g))
            res += dfs(a, 0, g, btoa, A, B);
    }
}

void traverse(int curr, vector<vi> &adj, vector<vi> &out, unordered_set<int> &visited, bool x){
    if (visited.count(curr) > 0) return;
    visited.insert(curr);
    if (x) out[curr] = adj[curr];
    for (int child : adj[curr]){
        traverse(child, adj, out, visited, !x);
    }
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

    // adjacency list
    vector<vi> graph(numVertices+1, vi());
    for (int i = 1; i < numVertices + 1; i++) {
        int numEdges, vertex;
        inputFile >> numEdges;
        for (int j = 0; j < numEdges; j++) {
            inputFile >> vertex;
            graph[i].push_back(vertex);
        }
    }
    inputFile.close();

    // build bipartite graph
    vector<vi> bipartite(numVertices+1, vi());
    unordered_set<int> visited;
    for (int i = 1; i < numVertices + 1; i++) {
        traverse(i, graph, bipartite, visited, true);
    }

    // solve
    vi btoa(numVertices+1, -1);
    hopcroftKarp(bipartite, btoa);

    // remove nodes
    vector<int> removedNodes;
    for (int i = 1; i < numVertices + 1; i++) {
        if (btoa[i] != -1) removedNodes.push_back(btoa[i]);
    }

    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "start to finish " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 60000000.0 << "[m]" << endl;

    // create output file
    outputFile << removedNodes.size() << endl;
    for (int node : removedNodes) outputFile << node << " ";
    outputFile.close();
}

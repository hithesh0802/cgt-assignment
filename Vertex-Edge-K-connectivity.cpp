#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <queue>
#include <cstring>
using namespace std;

#define INF INT_MAX

// Function to perform BFS and find an augmenting path in the residual graph
bool bfs(vector<vector<int>>& residualGraph, int source, int sink, vector<int>& parent) {
    int n = residualGraph.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; v++) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
                if (v == sink) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Function to find the maximum flow using Ford-Fulkerson method
int fordFulkerson(vector<vector<int>>& graph, int source, int sink) {
    int u, v;
    int n = graph.size();
    vector<vector<int>> residualGraph = graph;
    vector<int> parent(n);
    int maxFlow = 0;

    while (bfs(residualGraph, source, sink, parent)) {
        int pathFlow = INF;
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

// Function to find the edge connectivity of the graph
int edgeConnectivity(vector<vector<int>>& graph) {
    int n = graph.size();
    int minCut = INF;

    for (int i = 1; i < n; i++) {
        minCut = min(minCut, fordFulkerson(graph, 0, i));
    }

    return minCut;
}

// Function to find vertex connectivity using Menger's theorem
int vertexConnectivity(vector<vector<int>>& graph) {
    int n = graph.size();
    int minVertexCut = INF;

    for (int u = 0; u < n; u++) {
        for (int v = u + 1; v < n; v++) {
            // Create a modified graph where each vertex is split into two connected by an edge of capacity 1
            vector<vector<int>> modifiedGraph(2 * n, vector<int>(2 * n, 0));

            for (int i = 0; i < n; i++) {
                modifiedGraph[i][i + n] = 1; // split vertices with a capacity of 1
            }

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (graph[i][j] > 0) {
                        modifiedGraph[i + n][j] = graph[i][j];
                    }
                }
            }

            // Find minimum cut in this modified graph
            int cutValue = fordFulkerson(modifiedGraph, u + n, v);
            minVertexCut = min(minVertexCut, cutValue);
        }
    }

    return minVertexCut;
}

// Function to find the value of K for which the graph is K-connected
int findKConnectivity(int vertexConnectivity, int edgeConnectivity) {
    return min(vertexConnectivity, edgeConnectivity);
}

int main() {
    int n;
    cout << "Enter the number of vertices: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n, 0));

    cout << "Enter the weighted adjacency matrix (enter 0 for no edge):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    int edgeConn = edgeConnectivity(graph);
    int vertexConn = vertexConnectivity(graph);
    int kConnected = findKConnectivity(vertexConn, edgeConn);

    cout << "\nEdge Connectivity of the graph: " << edgeConn << endl;
    cout << "Vertex Connectivity of the graph: " << vertexConn << endl;
    cout << "The graph is " << kConnected << "-connected." << endl;

    return 0;
}

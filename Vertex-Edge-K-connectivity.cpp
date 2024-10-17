#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100005;

vector<int> adj[N]; // Adjacency list
bool visited[N]; // Visited array

// Function to perform DFS traversal
void DFS(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            DFS(v);
        }
    }
}

// Function to check if the graph is K-connected
bool isKConnected(int n, int K) {
    if (K < 1 || K >= n) {
        return false; // Invalid K values
    }

    // Check connectivity after removing up to K-1 vertices
    for (int u = 0; u < n; u++) {
        // Clear the visited array for new DFS
        memset(visited, false, sizeof(visited));
        
        // Mark the current vertex as removed
        vector<bool> removed(n, false);
        removed[u] = true;

        // Start DFS from the first non-removed vertex
        int startVertex = -1;
        for (int i = 0; i < n; i++) {
            if (!removed[i]) {
                startVertex = i;
                break; // Found a vertex to start DFS
            }
        }

        if (startVertex == -1) {
            continue; // All vertices are removed
        }

        // Perform DFS to see how many vertices are reachable
        DFS(startVertex);
        
        // Count the number of reachable vertices
        int countReachable = 0;
        for (int i = 0; i < n; i++) {
            if (!removed[i] && visited[i]) {
                countReachable++;
            }
        }

        // If the number of reachable vertices is less than n - (K - 1),
        // the graph is not K-connected
        if (countReachable < (n - K)) {
            return false; // Not K-connected
        }
    }

    return true; // The graph is K-connected
}

int main() {
    int n = 5; // Number of vertices
    // Example edges for the graph
    adj[0] = {1, 2}; // 0 is connected to 1 and 2
    adj[1] = {0, 2, 3}; // 1 is connected to 0, 2, and 3
    adj[2] = {0, 1, 3, 4}; // 2 is connected to 0, 1, 3, and 4
    adj[3] = {1, 2, 4}; // 3 is connected to 1, 2, and 4
    adj[4] = {2, 3}; // 4 is connected to 2 and 3

    // Check for K-connectivity for K = 1, 2, and 3
    for (int K = 1; K <= 3; K++) {
        if (isKConnected(n, K)) {
            cout << "The graph is " << K << "-connected." << endl;
        } else {
            cout << "The graph is not " << K << "-connected." << endl;
        }
    }

    return 0;
}

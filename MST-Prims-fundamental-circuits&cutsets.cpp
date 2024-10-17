#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <climits>
#include <set>
using namespace std;

class Graph {
    int V;
    list<pair<int, int>>* adj;  // List of pairs to store vertex and edge weight
    vector<pair<int, pair<int, int>>> allEdges; // To store all edges and their weights

public:
    Graph(int V) {
        this->V = V;
        adj = new list<pair<int, int>>[V];
    }
    ~Graph() { delete[] adj; }

    void addEdge(int u, int v, int weight) {
        adj[u].push_back(make_pair(v, weight));
        adj[v].push_back(make_pair(u, weight));
        allEdges.push_back({weight, {u, v}});  // Store all edges for circuits and cutsets
    }

    void primMST(vector<pair<int, int>>& mst) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> key(V, INT_MAX);
        vector<int> parent(V, -1);
        vector<bool> inMST(V, false);

        int start = 0;
        pq.push(make_pair(0, start));
        key[start] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (inMST[u])
                continue;

            inMST[u] = true;

            for (auto it : adj[u]) {
                int v = it.first;
                int weight = it.second;

                if (!inMST[v] && key[v] > weight) {
                    key[v] = weight;
                    pq.push(make_pair(key[v], v));
                    parent[v] = u;
                }
            }
        }

        for (int i = 1; i < V; i++) {
            mst.push_back({parent[i], i});
        }
    }

    void findFundamentalCircuits(const vector<pair<int, int>>& mst) {
        set<pair<int, int>> mstEdges;
        for (auto& edge : mst)
            mstEdges.insert({min(edge.first, edge.second), max(edge.first, edge.second)});

        cout << "\nFundamental Circuits:\n";
        for (auto& edge : allEdges) {
            int u = edge.second.first;
            int v = edge.second.second;

            if (mstEdges.find({min(u, v), max(u, v)}) == mstEdges.end()) {
                cout << "Adding edge (" << u << ", " << v << ") creates a fundamental circuit.\n";
            }
        }
    }

    void findFundamentalCutsets(const vector<pair<int, int>>& mst) {
        cout << "\nFundamental Cutsets:\n";
        for (auto& edge : mst) {
            cout << "Removing edge (" << edge.first << ", " << edge.second << ") creates a fundamental cutset.\n";
        }
    }
};

int main() {
    int V = 5;
    Graph g(V);

    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 4, 3);
    g.addEdge(3, 4, 2);

    vector<pair<int, int>> mst;
    g.primMST(mst);

    cout << "Minimum Spanning Tree (Prim's Algorithm):\n";
    for (auto& edge : mst)
        cout << edge.first << " - " << edge.second << "\n";

    g.findFundamentalCircuits(mst);
    g.findFundamentalCutsets(mst);

    return 0;
}

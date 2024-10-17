#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Graph {
    int V;
    list<pair<int, int>>* adj;  

public:
    Graph(int V) {
        this->V = V;
        adj = new list<pair<int, int>>[V];
    }
    ~Graph() { delete[] adj; }

    void addEdge(int u, int v, int weight) {
        adj[u].push_back(make_pair(v, weight));
        adj[v].push_back(make_pair(u, weight));
    }

    void dijkstra(int start) {
        vector<int> dist(V, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[start] = 0;
        pq.push(make_pair(0, start));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto i : adj[u]) {
                int v = i.first;
                int weight = i.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        cout << "Vertex   Distance from Source\n";
        for (int i = 0; i < V; ++i)
            cout << i << "\t\t" << dist[i] << "\n";
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

    int start;
    cout << "Enter starting vertex: (any integer from 0 to V-1)";
    cin >> start;
    cout<< "Your Source: "<< start << endl;
    g.dijkstra(start);

    return 0;
}

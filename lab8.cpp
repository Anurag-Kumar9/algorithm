#include <iostream>
#include <unordered_map>
#include <list>
#include <set>
#include <vector>
#include <limits.h>
#include <queue>

using namespace std;

class Graph {
    unordered_map<int, list<pair<int, int>>> adj; // Adjacency list
    unordered_map<int, int> vertexWeights; // Vertex weights
    vector<int> distance; // Distance from source

public:
    void addEdge(int u, int v, int weight) {
        adj[u].push_back(make_pair(v, weight));
    }

    void setNumOfVertices(int x) {
        distance.resize(x, INT_MAX);
    }

    void setVertexWeight(int vertex, int weight) {
        vertexWeights[vertex] = weight;
    }

    vector<int> dijkstra(int src) {
        distance[src] = 0; // Initialize source distance to 0
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            int dist = pq.top().first;
            int top = pq.top().second;
            pq.pop();

            if (dist > distance[top]) continue;

            for (auto neighbour : adj[top]) {
                int newDistance = distance[top] + neighbour.second;
                if (distance[neighbour.first] > newDistance) {
                    distance[neighbour.first] = newDistance;
                    pq.push({distance[neighbour.first], neighbour.first});
                }
            }
        }
        return distance;
    }
};

int main() {
    Graph g;
    g.setNumOfVertices(5);
    g.setVertexWeight(0, 5);
    g.setVertexWeight(1, 1);
    g.setVertexWeight(2, 2);
    g.setVertexWeight(3, 3);
    g.setVertexWeight(4, 4);
    
    g.addEdge(0, 1, 10);
    g.addEdge(0, 4, 3);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 4, 4);
    g.addEdge(2, 3, 9);
    g.addEdge(3, 2, 7);
    g.addEdge(4, 1, 1);
    g.addEdge(4, 2, 8);
    g.addEdge(4, 3, 2);
    
    int src = 0; // Starting vertex
    vector<int> distances = g.dijkstra(src);
    
    cout << "Vertex Distances from Source (" << src << "):" << endl;
    for (int i = 0; i < distances.size(); i++) {
        cout << "Distance to vertex " << i << ": " 
             << (distances[i] == INT_MAX ? "INF" : to_string(distances[i])) << endl;
    }
    
    return 0;
}

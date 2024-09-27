#include <iostream>
#include <unordered_map>
#include <list>
#include <set>
#include <vector>
#include <limits.h>

using namespace std;

class Graph {
    unordered_map<int, list<pair<int, int>>> adj;
    int numOfVertices;
    unordered_map<int, int> vertexWeights; 
    vector<int> distance;
    vector<int> cumulativeVertexWeight;
    set<pair<int, int>> s; // here first int -> distance & second int -> node

public:
    void addEdge(int u, int v, int weight) {
        adj[u].push_back(make_pair(v, weight));
    }

    void setNumOfVertices(int x) {
        this->numOfVertices = x;
        distance.resize(x, INT_MAX);
        cumulativeVertexWeight.resize(x, 0);
    }

    void setVertexWeight(int vertex, int weight) {
        vertexWeights[vertex] = weight;
    }

    int getVertexWeight(int vertex) {
        return vertexWeights[vertex];
    }

    vector<int> dijkstra(int src) {
        distance[src] = 0;
        cumulativeVertexWeight[src] = 0; 
        s.insert(make_pair(distance[src], src));

        while (!s.empty()) {
            int top = s.begin()->second;
            s.erase(s.begin());

            for (auto neighbour : adj[top]) {
                int newDistance = distance[top] + neighbour.second + cumulativeVertexWeight[top];
                if (distance[neighbour.first] > newDistance) {
                    s.erase(make_pair(distance[neighbour.first], neighbour.first));
                    distance[neighbour.first] = newDistance;
                    cumulativeVertexWeight[neighbour.first] = cumulativeVertexWeight[top] + vertexWeights[neighbour.first];
                    s.insert(make_pair(distance[neighbour.first], neighbour.first));
                }
            }
        }
        return distance;
    }
};

int main() {
    /*Vertices: 5
    Edges: (0 -> 1, 10), (0 -> 4, 3), (1 -> 2, 2), (1 -> 4, 4), (2 -> 3, 9), (3 -> 2, 7), (4 -> 1, 1), (4 -> 2, 8), (4 -> 3, 2)
    Vertex Weights: 0, 1, 2, 3, 4
    */
    Graph g;
    g.setNumOfVertices(5);
    g.setVertexWeight(0, 50);
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
    vector<int> distances = g.dijkstra(0);
    for (auto i : distances) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
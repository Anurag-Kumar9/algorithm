//obtain topological ordering of vertices in a diagraph
//implementing topological Sort using Kahn's Algorithm on directed acyclic graph(disconnected graph is not included)
#include <iostream>
#include <unordered_map>
#include <queue>
#include <list>
#include <vector>

using namespace std;

class Graph {
    unordered_map<int, list<int>>adj;
    int numOfVertices;
    unordered_map<int, int> inDegree;
    queue<int> q;
    vector<int> topologicalOrder;
public:
    void getNumOfVertices(int x) {
        this -> numOfVertices = x;
    }
    void getEdges(int u, int v){
        adj[u].push_back(v);
    }
    void getIndegree(){
        for(int i = 0; i < numOfVertices; i++){
            this->inDegree[i] = 0;
        }
        for(int i = 0; i < numOfVertices; i++){
            for(auto neighbour : adj[i]){
                this->inDegree[neighbour]++;
            }
        }
    }
    vector<int> topologicalSort() {
        this->getIndegree();
        for(int i = 0; i < numOfVertices; i++){
            if(inDegree[i] == 0){
                q.push(i);
            }
        }
        while(!q.empty()){
            int front = q.front();
            q.pop();
            topologicalOrder.push_back(front);
            for(auto neighbour: adj[front]){
                inDegree[neighbour]--;
                if(inDegree[neighbour] == 0){
                    q.push(neighbour);
                }
            }
        }
        if (topologicalOrder.size() != numOfVertices) {
            cout << "Cycle detected in the graph. Topological sort not possible." << endl;
            return {};
        }
        return topologicalOrder;
    }
};

int main() {
    Graph g;
    g.getNumOfVertices(6);
    g.getEdges(5, 2);
    g.getEdges(5, 0);
    g.getEdges(4, 0);
    g.getEdges(4, 1);
    g.getEdges(2, 3);
    g.getEdges(3, 1);

    vector<int> topologicalOrder = g.topologicalSort();
    if (!topologicalOrder.empty()) {
        cout << "Topological Sort: ";
        for (int node : topologicalOrder) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}

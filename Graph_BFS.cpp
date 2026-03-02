#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph
{
    int V;                     // Number of vertices
    vector<int> *adj;          // Adjacency list

public:
    Graph(int vertices)
    {
        V = vertices;
        adj = new vector<int>[V];
    }

    // Add edge
    void addEdge(int u, int v, bool isDirected)
    {
        adj[u].push_back(v);

        if(!isDirected)        // If undirected graph
            adj[v].push_back(u);
    }

    // BFS Traversal
    void BFS(int start)
    {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS Traversal: ";

        while(!q.empty())
        {
            int node = q.front();
            q.pop();

            cout << node << " ";

            for(int i = 0; i < adj[node].size(); i++)
            {
                int neighbour = adj[node][i];

                if(!visited[neighbour])
                {
                    visited[neighbour] = true;
                    q.push(neighbour);
                }
            }
        }
    }
};

int main()
{
    int vertices, edges;
    cout << "Enter number of vertices: ";
    cin >> vertices;

    Graph g(vertices);

    cout << "Enter number of edges: ";
    cin >> edges;

    int choice;
    cout << "Enter 1 for Directed Graph, 0 for Undirected Graph: ";
    cin >> choice;

    cout << "Enter edges (u v):\n";
    for(int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v, choice);
    }

    int start;
    cout << "Enter starting vertex for BFS: ";
    cin >> start;

    g.BFS(start);

    return 0;
}
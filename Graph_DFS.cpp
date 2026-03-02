#include <iostream>
#include <vector>
using namespace std;

class Graph
{
    int V;                      // Number of vertices
    vector<int> *adj;           // Adjacency list

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

        if(!isDirected)         // If undirected graph
            adj[v].push_back(u);
    }

    // DFS utility function
    void DFSUtil(int v, vector<bool> &visited)
    {
        visited[v] = true;
        cout << v << " ";

        for(int i = 0; i < adj[v].size(); i++)
        {
            int neighbour = adj[v][i];

            if(!visited[neighbour])
                DFSUtil(neighbour, visited);
        }
    }

    // DFS Traversal
    void DFS(int start)
    {
        vector<bool> visited(V, false);

        cout << "DFS Traversal: ";
        DFSUtil(start, visited);
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
    cout << "Enter starting vertex for DFS: ";
    cin >> start;

    g.DFS(start);

    return 0;
}
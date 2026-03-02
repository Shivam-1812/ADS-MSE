#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define MAX 20

class Graph
{
    int V;
    string cities[MAX];
    int cost[MAX][MAX];

public:
    Graph(int vertices)
    {
        V = vertices;

        for(int i = 0; i < V; i++)
            for(int j = 0; j < V; j++)
                cost[i][j] = 0;
    }

    void inputCities()
    {
        cout << "Enter city names:\n";
        for(int i = 0; i < V; i++)
            cin >> cities[i];
    }

    void addRoute(int u, int v, int w)
    {
        cost[u][v] = w;
        cost[v][u] = w;   // Undirected graph
    }

    void display()
    {
        cout << "\nTransportation Network (Adjacency Matrix):\n";
        cout << "   ";
        for(int i = 0; i < V; i++)
            cout << cities[i] << " ";
        cout << endl;

        for(int i = 0; i < V; i++)
        {
            cout << cities[i] << " ";
            for(int j = 0; j < V; j++)
                cout << cost[i][j] << " ";
            cout << endl;
        }
    }

    void primMST()
    {
        int parent[MAX];
        int key[MAX];
        bool mstSet[MAX];

        for(int i = 0; i < V; i++)
        {
            key[i] = INT_MAX;
            mstSet[i] = false;
        }

        key[0] = 0;
        parent[0] = -1;

        for(int count = 0; count < V - 1; count++)
        {
            int min = INT_MAX, u;

            for(int v = 0; v < V; v++)
                if(!mstSet[v] && key[v] < min)
                {
                    min = key[v];
                    u = v;
                }

            mstSet[u] = true;

            for(int v = 0; v < V; v++)
                if(cost[u][v] && !mstSet[v] && cost[u][v] < key[v])
                {
                    parent[v] = u;
                    key[v] = cost[u][v];
                }
        }

        cout << "\nMinimum Spanning Tree:\n";
        int total = 0;

        for(int i = 1; i < V; i++)
        {
            cout << cities[parent[i]] << " - "
                 << cities[i] << "  Distance: "
                 << cost[i][parent[i]] << endl;
            total += cost[i][parent[i]];
        }

        cout << "Total Minimum Distance: " << total << endl;
    }
};

int main()
{
    int V, E;

    cout << "Enter number of cities: ";
    cin >> V;

    Graph g(V);

    g.inputCities();

    cout << "Enter number of routes: ";
    cin >> E;

    cout << "Enter routes (city1_index city2_index distance):\n";
    for(int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g.addRoute(u, v, w);
    }

    g.display();
    g.primMST();

    return 0;
}
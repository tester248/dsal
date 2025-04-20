#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Prims {
private:
    int vertices, edges;
    vector<vector<int>> adjMatrix;

public:
    Prims(int v, int e) {
        vertices = v;
        edges = e;
        adjMatrix.resize(vertices, vector<int>(vertices, 0));  
    }

    void add_edge() {
        cout << "Enter edges (source destination weight):\n";
        for (int i = 0; i < edges; i++) {
            int source, dest, weight;
            cin >> source >> dest >> weight;

            if (source >= 0 && source < vertices && dest >= 0 && dest < vertices) {
                adjMatrix[source][dest] = weight;
                adjMatrix[dest][source] = weight;
            } else {
                cout << "Invalid edge! Please enter valid vertices.\n";
                i--;  
            }
        }
    }

    void display() {
        cout << "\nAdjacency Matrix:\n  ";
        for (int i = 0; i < vertices; i++) {
            cout << i << " ";
        }
        cout << "\n";

        for (int i = 0; i < vertices; i++) {
            cout << i << " ";
            for (int j = 0; j < vertices; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << "\n";
        }
    }

    int minkey(bool visited[], int key[]) {
        int min = INT_MAX, min_index;
        for (int i = 0; i < vertices; i++) {
            if (!visited[i] && key[i] < min) {
                min = key[i];
                min_index = i;
            }
        }
        return min_index;
    }

    void prims() {
        int parent[vertices];
        int key[vertices];
        bool visited[vertices];
        
        for (int i = 0; i < vertices; i++) {
            key[i] = INT_MAX;
            visited[i] = false;
        }
        
        key[0] = 0;
        parent[0] = -1;
        
        for (int count = 0; count < vertices - 1; count++) {
            int u = minkey(visited, key);
            visited[u] = true;
            
            for (int v = 0; v < vertices; v++) {
                if (adjMatrix[u][v] != 0 && !visited[v] && adjMatrix[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = adjMatrix[u][v];
                }
            }
        }
        
        printMST(parent);
    }
    
    void printMST(int parent[]) {
        cout << "\nMinimum Spanning Tree (Phone Line Connections):" << endl;
        cout << "Edge \tWeight" << endl;
        int total_cost = 0;
        
        for (int i = 1; i < vertices; i++) {
            cout << parent[i] << " - " << i << "\t" << adjMatrix[parent[i]][i] << endl;
            total_cost += adjMatrix[parent[i]][i];
        }
        
        cout << "\nTotal cost of the minimum spanning tree: " << total_cost << endl;
        cout << "\nThese are the optimal phone line connections between offices." << endl;
    }
};

int main() {
    int vertices, edges;
    cout << "Enter the number of offices (vertices): ";
    cin >> vertices;
    cout << "Enter the number of possible connections (edges): ";
    cin >> edges;

    Prims p(vertices, edges);
    p.add_edge();

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Print Adjacency Matrix\n";
        cout << "2. Find Minimum Spanning Tree using Prim's Algorithm\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                p.display();
                break;
            case 2:
                p.prims();
                break;
            case 3:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}

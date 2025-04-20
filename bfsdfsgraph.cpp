#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <iomanip>

using namespace std;

class Graph {
private:
    int vertices;
    map<string, int> landmarkIndex; 
    map<int, string> indexLandmark; 
    vector<vector<int>> adjMatrix;
    map<int, vector<int>> adjList; 

public:
    Graph(int v) : vertices(v) {
        adjMatrix.resize(vertices, vector<int>(vertices, 0));
    }

    void addLandmark(string name, int index) {
        landmarkIndex[name] = index;
        indexLandmark[index] = name;
    }

    void addEdge(string src, string dest) {
        if (landmarkIndex.find(src) == landmarkIndex.end() || landmarkIndex.find(dest) == landmarkIndex.end()) {
            cout << "Invalid landmarks entered!\n";
            return;
        }
        int u = landmarkIndex[src];
        int v = landmarkIndex[dest];
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; 
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void displayGraph() {
        int maxWidth = 0;
        for (int i = 0; i < vertices; i++) {
            int nameLength = indexLandmark[i].length();
            if (nameLength > maxWidth) {
                maxWidth = nameLength;
            }
        }
        
        maxWidth += 2;
        
        cout << "\nAdjacency Matrix:\n" << setw(maxWidth) << "";
        for (int i = 0; i < vertices; i++) {
            cout << setw(maxWidth) << left << indexLandmark[i];
        }
        cout << "\n";

        for (int i = 0; i < vertices; i++) {
            cout << setw(maxWidth) << left << indexLandmark[i];
            for (int j = 0; j < vertices; j++) {
                cout << setw(maxWidth) << left << adjMatrix[i][j];
            }
            cout << endl;
        }

        cout << "\nAdjacency List:\n";
        for (auto &pair : adjList) {
            cout << setw(maxWidth) << left << indexLandmark[pair.first] << "-> ";
            for (int neighbor : pair.second) {
                cout << indexLandmark[neighbor] << " ";
            }
            cout << endl;
        }
    }

    void dfs() {
        vector<bool> visited(vertices, false);
        cout << "DFS Traversal: ";

        for (int i = 0; i < vertices; i++) { 
            if (!visited[i]) { 
                stack<int> s;
                s.push(i);

                while (!s.empty()) {
                    int node = s.top();
                    s.pop();

                    if (!visited[node]) {
                        cout << indexLandmark[node] << " ";
                        visited[node] = true;

                        for (int j = vertices - 1; j >= 0; j--) {
                            if (adjMatrix[node][j] != 0 && !visited[j]) {
                                s.push(j);
                            }
                        }
                    }
                }
            }
        }
        cout << endl;
    }

    void bfs() {
        vector<bool> visited(vertices, false);
        cout << "BFS Traversal: ";

        for (int i = 0; i < vertices; i++) { 
            if (!visited[i]) { 
                queue<int> q;
                visited[i] = true;
                q.push(i);

                while (!q.empty()) {
                    int node = q.front();
                    q.pop();
                    cout << indexLandmark[node] << " ";

                    for (int neighbor : adjList[node]) {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
            }
        }
        cout << endl;
    }

    void dfsRecursiveUtil(int node, vector<bool> &visited) {
        cout << indexLandmark[node] << " ";
        visited[node] = true;

        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                dfsRecursiveUtil(neighbor, visited);
            }
        }
    }

    void dfsRecursive() {
        vector<bool> visited(vertices, false);
        cout << "DFS Recursive Traversal: ";

        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                dfsRecursiveUtil(i, visited);
            }
        }
        cout << endl;
    }

    void dfsNonRecursive() {
        vector<bool> visited(vertices, false);
        cout << "DFS Non-Recursive Traversal: ";

        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                stack<int> s;
                s.push(i);

                while (!s.empty()) {
                    int node = s.top();
                    s.pop();

                    if (!visited[node]) {
                        cout << indexLandmark[node] << " ";
                        visited[node] = true;

                        for (int j = vertices - 1; j >= 0; j--) {
                            if (adjMatrix[node][j] != 0 && !visited[j]) {
                                s.push(j);
                            }
                        }
                    }
                }
            }
        }
        cout << endl;
    }
};

int main() {
    int landmarks_no;
    cout << "Enter the number of landmarks: ";
    cin >> landmarks_no;
    cin.ignore();

    Graph g(landmarks_no);
    cout << "Enter landmark names:\n";
    for (int i = 0; i < landmarks_no; i++) {
        string name;
        getline(cin, name);
        g.addLandmark(name, i);
    }

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Edge\n";
        cout << "2. Display Graph\n";
        cout << "3. Perform Recursive DFS\n";
        cout << "4. Perform Non-Recursive DFS\n";
        cout << "5. Perform BFS\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string src, dest;
                cout << "Enter source landmark: ";
                getline(cin, src);
                cout << "Enter destination landmark: ";
                getline(cin, dest);
                g.addEdge(src, dest);
                break;
            }
            case 2:
                g.displayGraph();
                break;
            case 3:
                g.dfsRecursive();
                break;
            case 4:
                g.dfsNonRecursive();
                break;
            case 5:
                g.bfs();
                break;
            case 6:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
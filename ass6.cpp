#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <map>
using namespace std;

class Graph {
private:
    int num;
    vector<vector<int>> adjMatrix;
    map<string, int> landmarkIndex;
    map<int, string> indexLandmark;

public:
    Graph(int n, vector<string> landmarkNames) {
        num = n;
        adjMatrix.resize(num, vector<int>(num, 0));

        for (int i = 0; i < num; i++) {
            landmarkIndex[landmarkNames[i]] = i;
            indexLandmark[i] = landmarkNames[i];
        }
    }

    void add_edge(string src, string dest) {
        if (landmarkIndex.find(src) == landmarkIndex.end() || landmarkIndex.find(dest) == landmarkIndex.end()) {
            cout << "Invalid landmarks entered!\n";
            return;
        }

        int u = landmarkIndex[src];
        int v = landmarkIndex[dest];

        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }

    void bfs(string start) {
        if (landmarkIndex.find(start) == landmarkIndex.end()) {
            cout << "Invalid starting landmark!\n";
            return;
        }

        int startIndex = landmarkIndex[start];
        vector<bool> visited(num, false);
        queue<int> q;

        cout << "BFS Traversal: ";
        visited[startIndex] = true;
        q.push(startIndex);

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << indexLandmark[node] << " ";

            for (int i = 0; i < num; i++) {
                if (adjMatrix[node][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        cout << endl;
    }

    void dfs(string start) {
        if (landmarkIndex.find(start) == landmarkIndex.end()) {
            cout << "Invalid starting landmark!\n";
            return;
        }

        int startIndex = landmarkIndex[start];
        stack<int> s;
        vector<bool> visited(num, false);

        cout << "DFS Traversal: ";
        s.push(startIndex);

        while (!s.empty()) {
            int node = s.top();
            s.pop();

            if (!visited[node]) {
                cout << indexLandmark[node] << " ";
                visited[node] = true;

                for (int i = num - 1; i >= 0; i--) {
                    if (adjMatrix[node][i] == 1 && !visited[i]) {
                        s.push(i);
                    }
                }
            }
        }
        cout << endl;
    }

    void display() {
        cout << "Adjacency Matrix for the Graph:\n";
        for (int i = 0; i < num; ++i) {
            for (int j = 0; j < num; ++j) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int landmarks_no;
    cout << "Enter the number of landmarks: ";
    cin >> landmarks_no;

    vector<string> landmarkNames(landmarks_no);
    cout << "Enter landmark names:\n";
    for (int i = 0; i < landmarks_no; ++i) {
        cin >> landmarkNames[i];
    }

    Graph g(landmarks_no, landmarkNames);

    while (true) {
        cout << "\n1. Add connection (edge)\n";
        cout << "2. Display Graph\n";
        cout << "3. Perform BFS\n";
        cout << "4. Perform DFS\n";
        cout << "5. Exit\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string src, dest;
                cout << "Enter source landmark: ";
                cin >> src;
                cout << "Enter destination landmark: ";
                cin >> dest;
                g.add_edge(src, dest);
                break;
            }
            case 2: {
                g.display();
                break;
            }
            case 3: {
                string start;
                cout << "Enter starting landmark for BFS: ";
                cin >> start;
                g.bfs(start);
                break;
            }
            case 4: {
                string start;
                cout << "Enter starting landmark for DFS: ";
                cin >> start;
                g.dfs(start);
                break;
            }
            case 5: {
                cout << "Exiting program...\n";
                return 0;
            }
            default:
                cout << "Invalid choice. Please choose a valid option.\n";
        }
    }
}



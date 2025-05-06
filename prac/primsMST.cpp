#include<iostream>
#include<vector>
#include<climits>
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

        void addEdge(){
            cout<<"Enter edges (source destination weight):"<<endl;
            for(int i =0; i<edges; i++){
                int source, dest, weight;
                cin >>source>>dest>>weight;
                if(source >= 0 && source < vertices && dest >= 0 && dest < vertices){
                    adjMatrix[source][dest] = weight;
                    adjMatrix[dest][source] = weight;
                } else{
                    cout<<"Invalid edge! Please enter valid vertices."<<endl;
                    i--;
                }
            }
        }

        void display(){
            cout <<endl<< "Adjacency Matrix:" <<endl<< "  ";
            for(int i=0; i < vertices; i++)
                cout << i << " ";
            cout <<endl;

            for(int i = 0 ; i < vertices; i++){
                cout << i << " ";
                for(int j = 0; j < vertices; j++){
                    cout << adjMatrix[i][j] << " ";
                }
                cout <<endl;
            }
        }

        void prims()
        {
            int parent[vertices];
            int minWeight[vertices];
            bool visited[vertices];
            for(int i = 0; i < vertices; i++){
                minWeight[i] = INT_MAX;
                visited[i] = false;
            }
            minWeight[0] = 0;
            parent[0]= -1;
            for(int edgeCount = 0; edgeCount < vertices - 1; edgeCount++){
                int vertex = minWeightVertex(visited, minWeight);
                visited[vertex] = true;

                for(int j = 0; j < vertices; j++){
                    if(adjMatrix[vertex][j] && !visited[j] && adjMatrix[vertex][j] < minWeight[j])
                    {
                        parent[j] = vertex;
                        minWeight[j] = adjMatrix[vertex][j];
                    }
                }
            }
            printMST(parent);
        }

        int minWeightVertex(bool visited[], int minWeight[]){
            int min = INT_MAX;
            int minIndex;
            for(int i=0; i < vertices -1 ; i++){
                if(!visited[i] && minWeight[i] < min){
                    min = minWeight[i];
                    minIndex = i;
                }
            }
            return minIndex;
        }

        void printMST(int parent[]){
            cout << endl << "Minimum Spanning Tree (Phone Line Connections):" << endl;
            cout << "Edge \tWeight" << endl;
            int totalCost = 0;
            for(int i = 1; i < vertices; i++){
                cout << parent[i] << " - " << i << "\t" << adjMatrix[parent[i]][i] << endl;
                totalCost += adjMatrix[parent[i]][i];
            }
            cout << "\nTotal cost of the minimum spanning tree: " << totalCost << endl;
        }
};

int main(){
    int vertices, edges;
    cout << "Enter number of vertices(offices): ";
    cin >> vertices;
    cout << "Enter number of edges(phone lines): ";
    cin >> edges;
    Prims p(vertices, edges);
    p.addEdge();

    int choice;
    while(true){
        cout << endl << "====MENU====" << endl;
        cout << "1. Display Adjacency Matrix" << endl;
        cout << "2. Find Minimum Spanning Tree" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice){
            case 1:
                p.display();
                break;
            case 2:
                p.prims();
                break;
            case 3:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
}
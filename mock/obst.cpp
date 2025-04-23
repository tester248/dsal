#include <iostream>
#include <iomanip> 
#include <climits> 
using namespace std;

struct TreeNode {
    string key;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(string k) : key(k), left(nullptr), right(nullptr) {}
};

double calculateOBSTWeight(const double* P, const double* Q, int n) {
    double W[101][101] = {0};

    for (int i = 0; i <= n; i++) {
        W[i][i] = Q[i];
    }
    for (int i = 0; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            W[i][j] = W[i][j - 1] + P[j - 1] + Q[j];
        }
    }

    cout << "Weights in OBST format by level:" << endl;
    for (int level = 0; level <= n; level++) {
        for (int i = 0; i + level <= n; i++) {
            int j = i + level;
            cout << "W[" << i << "][" << j << "] = " << W[i][j] << " ";
        }
        cout << endl;
    }

    return W[0][n];
}

double calculateOBSTCost(const double* P, const double* Q, int n) {
    double W[101][101] = {0};
    double C[101][101] = {0};

    for (int i = 0; i <= n; i++) {
        W[i][i] = Q[i];
        C[i][i] = 0;
    }
    for (int i = 0; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            W[i][j] = W[i][j - 1] + P[j - 1] + Q[j];
        }
    }
    for (int level = 1; level <= n; level++) {
        for (int i = 0; i + level <= n; i++) {
            int j = i + level;
            C[i][j] = INT_MAX;
            for (int r = i; r < j; r++) {
                double cost = C[i][r] + C[r + 1][j] + W[i][j];
                if (cost < C[i][j]) {
                    C[i][j] = cost;
                }
            }
        }
    }

    cout << "Costs in OBST format by level:" << endl;
    for (int level = 0; level <= n; level++) {
        for (int i = 0; i + level <= n; i++) {
            int j = i + level;
            cout << "C[" << i << "][" << j << "] = " << C[i][j] << " ";
        }
        cout << endl;
    }

    return C[0][n];
}

int calculateOBSTRoots(const double* P, const double* Q, int n, int R[101][101]) {
    double W[101][101] = {0};
    double C[101][101] = {0};

    for (int i = 0; i <= n; i++) {
        W[i][i] = Q[i];
        C[i][i] = 0;
    }

    for (int i = 0; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            W[i][j] = W[i][j - 1] + P[j - 1] + Q[j];
        }
    }

    for (int level = 1; level <= n; level++) {
        for (int i = 0; i + level <= n; i++) {
            int j = i + level;
            C[i][j] = INT_MAX;
            for (int r = i + 1; r <= j; r++) {
                double cost = C[i][r - 1] + C[r][j] + W[i][j];
                if (cost < C[i][j]) {
                    C[i][j] = cost;
                    R[i][j] = r;  
                }
            }
        }
    }

    cout << "Roots in OBST format by level:" << endl;
    for (int level = 1; level <= n; level++) {
        for (int i = 0; i + level <= n; i++) {
            int j = i + level;
            cout << "R[" << i << "][" << j << "] = " << R[i][j] << " ";
        }
        cout << endl;
    }

    return R[0][n]; 
}

// Function to build the OBST using the R table
TreeNode* buildOptimalBST(int i, int j, int R[101][101], const string* keys) {
    if (i > j) return nullptr;
    
    int r = R[i][j];
    if (r == 0) return nullptr;
    
    TreeNode* root = new TreeNode(keys[r-1]);
    root->left = buildOptimalBST(i, r-1, R, keys);
    root->right = buildOptimalBST(r, j, R, keys);
    
    return root;
}

void inorderTraversal(TreeNode* root) {
    if (root == nullptr) return;
    inorderTraversal(root->left);
    cout << root->key << " ";
    inorderTraversal(root->right);
}

void preorderTraversal(TreeNode* root) {
    if (root == nullptr) return;
    cout << root->key << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void postorderTraversal(TreeNode* root) {
    if (root == nullptr) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->key << " ";
}

int main() {
    int n = 0;
    string keys[100];
    double P[100], Q[101];
    double weight = 0, cost = 0;
    int R[101][101] = {0};
    int root = 0;
    TreeNode* rootNode = nullptr;
    bool dataEntered = false;
    int choice;
    
    cout << "Enter the number of keys: ";
    cin >> n;
    
    cout << "Enter the keywords: ";
    for (int i = 0; i < n; i++)
        cin >> keys[i];

    cout << "Enter the probabilities of keys (P): ";
    for (int i = 0; i < n; i++) 
        cin >> P[i];

    cout << "Enter the probabilities of dummy keys (Q): ";
    for (int i = 0; i <= n; i++) 
        cin >> Q[i];
        
    dataEntered = true;
    cout << "Data entered successfully!\n";
    
    do {
        cout << "\n\n==== OPTIMAL BINARY SEARCH TREE MENU ====\n";
        cout << "1. Calculate and display OBST weight\n";
        cout << "2. Calculate and display OBST cost\n";
        cout << "3. Calculate and display OBST roots\n";
        cout << "4. Build OBST and display tree traversals\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                weight = calculateOBSTWeight(P, Q, n);
                cout << "The weight of the OBST is: " << weight << endl;
                break;
            case 2:
                cost = calculateOBSTCost(P, Q, n);
                cout << "The cost of the OBST is: " << cost << endl;
                break;
            case 3: 
                root = calculateOBSTRoots(P, Q, n, R);
                cout << "The root of the OBST is: " << root << endl;
                break;
            case 4:
                rootNode = buildOptimalBST(0, n, R, keys);
                
                cout << "\nTree Traversals:" << endl;
                cout << "Inorder: ";
                inorderTraversal(rootNode);
                cout << endl;
                
                cout << "Preorder: ";
                preorderTraversal(rootNode);
                cout << endl;
                
                cout << "Postorder: ";
                postorderTraversal(rootNode);
                cout << endl;
                break;
            case 5: 
                cout << "Exiting program. Goodbye!\n";
                break;
            default: 
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 5);
    return 0;
}
// Sample Input:
// Enter the number of keys: 4
// Enter the keywords: out float if while
// Enter the probabilities of keys (P): 1 4 2 1
// Enter the probabilities of dummy keys (Q): 4 2 4 1 1
// Data entered successfully!

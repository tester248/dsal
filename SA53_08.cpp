#include<iostream>
#include<string>
using namespace std;
#define MAX 10

struct Node {
    string key;
    Node* left;
    Node* right;
};

int n;
string keys[MAX];
int p[MAX];
int q[MAX + 1];
int w[MAX + 1][MAX + 1];
int c[MAX + 1][MAX + 1];
int r[MAX + 1][MAX + 1];

Node* creation(int i, int j) {
    if (i == j)
        return NULL;
    int rd = r[i][j];
    Node* root = new Node;
    root->key = keys[rd - 1];
    root->left = creation(i, rd - 1);
    root->right = creation(rd, j);
    return root;
}

void preorder(Node* root) {
    if (root == NULL)
        return;
    cout << root->key << " ";
    preorder(root->left);
    preorder(root->right);
}

void printMatrix(char title[], int mat[MAX + 1][MAX + 1]) {
    cout << "\n" << title << ":\n\n";
    cout << "      ";
    for (int j = 0; j <= n; j++)
        cout << " j=" << j << "  ";
    cout << "\n";

    for (int i = 0; i <= n; i++) {
        cout << "i=" << i << "  ";
        for (int j = 0; j <= n; j++) {
            if (j < i)
                cout << "       ";
            else {
                if (mat[i][j] < 10)
                    cout << "  " << mat[i][j] << "   ";
                else if (mat[i][j] < 100)
                    cout << " " << mat[i][j] << "   ";
                else
                    cout << mat[i][j] << "   ";
            }
        }
        cout << "\n";
    }
}

int main() {
    cout << "Enter Number of Keys: ";
    cin >> n;
    cout << "Enter " << n << " keys:\n";
    for (int i = 0; i < n; i++)
        cin >> keys[i];
    cout << "Enter " << n << " successful search frequencies (p):\n";
    for (int i = 0; i < n; i++)
        cin >> p[i];
    cout << "Enter " << n + 1 << " unsuccessful search frequencies (q):\n";
    for (int i = 0; i <= n; i++)
        cin >> q[i];

    for (int i = 0; i <= n; i++) {
        w[i][i] = q[i];
        c[i][i] = 0;
        r[i][i] = 0;
    }

    for (int m = 1; m <= n; m++) {
        for (int i = 0; i <= n - m; i++) {
            int j = i + m;
            w[i][j] = w[i][j - 1] + p[j - 1] + q[j];
            int minc = 999, minr = 0;
            for (int k = i + 1; k <= j; k++) {
                int cost = c[i][k - 1] + c[k][j];
                if (cost < minc) {
                    minc = cost;
                    minr = k;
                }
            }
            c[i][j] = w[i][j] + minc;
            r[i][j] = minr;
        }
    }

    printMatrix("Weight Matrix (w[i][j])", w);
    printMatrix("Cost Matrix (c[i][j])", c);
    printMatrix("Root Matrix (r[i][j])", r);

    Node* root = creation(0, n);
    cout << "\nPreorder Traversal of OBST:\n";
    preorder(root);
    cout << "\n";
    return 0;
}

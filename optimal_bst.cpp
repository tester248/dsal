#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// Function to build the Optimal Binary Search Tree
double optimalBST(const vector<double>& P, const vector<double>& Q, int n) {
    vector<vector<double>> W(n + 1, vector<double>(n + 1, 0));
    vector<vector<double>> C(n + 1, vector<double>(n + 1, 0));
    vector<vector<int>> R(n + 1, vector<int>(n + 1, 0));

    // Initialize weights and costs
    for (int i = 0; i <= n; i++) {
        W[i][i] = Q[i];
        C[i][i] = 0;
    }
    for (int i = 0; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            W[i][j] = W[i][j - 1] + P[j - 1] + Q[j];
        }
    }

    // Compute the cost and root for each subtree
    for (int length = 1; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            int j = i + length;
            C[i][j] = numeric_limits<double>::infinity();
            for (int r = i + 1; r <= j; r++) {
                double cost = C[i][r - 1] + C[r][j] + W[i][j];
                if (cost < C[i][j]) {
                    C[i][j] = cost;
                    R[i][j] = r;
                }
            }
        }
    }

    // Display the root table
    cout << "Root Table (R):" << endl;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (j >= i + 1) {
                cout << R[i][j] << " ";
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }

    return C[0][n];
}

int main() {
    int n;
    cout << "Enter the number of keys: ";
    cin >> n;

    vector<double> P(n), Q(n + 1);
    cout << "Enter the probabilities of keys (P): ";
    for (double& p : P) cin >> p;

    cout << "Enter the probabilities of dummy keys (Q): ";
    for (double& q : Q) cin >> q;

    double cost = optimalBST(P, Q, n);
    cout << "The cost of the Optimal Binary Search Tree is: " << cost << endl;

    return 0;
}

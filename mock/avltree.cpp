#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <atomic>

using namespace std;

struct Node {
public:
    string keyword;
    string meaning;
    Node* left;
    Node* right;
    int height;
    Node(string key, string m) {
        keyword = key;
        meaning = m;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

void printLevelOrder(Node* root);
Node* rightRotate(Node* y);
Node* leftRotate(Node* x);
int getHeight(Node* node);
void updateHeight(Node* node);
int calculateBalanceFactor(Node* node);
Node* findMinNode(Node* node);
Node* balanceTree(Node* node);

// Utility functions
int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

void updateHeight(Node* node) {
    if (node != nullptr) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

int calculateBalanceFactor(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Global flag to track if a rotation occurred during an operation
atomic<bool> rotation_occurred(false);

// Right rotation
Node* rightRotate(Node* y) {
    cout << "Performing Right Rotation at node: " << y->keyword << endl;
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    rotation_occurred = true;
    return x;
}

// Left rotation
Node* leftRotate(Node* x) {
    cout << "Performing Left Rotation at node: " << x->keyword << endl;
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    rotation_occurred = true;
    return y;
}

Node* findMinNode(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Helper function to balance the tree at a given node
Node* balanceTree(Node* node) {
    updateHeight(node);
    int balance = calculateBalanceFactor(node);
    Node* original_node = node;

    // Left Heavy
    if (balance > 1) {
        // Left-Right Case
        if (calculateBalanceFactor(node->left) < 0) {
            cout << "Tree before LR rotation (left part) at " << node->left->keyword << ":" << endl;
            printLevelOrder(original_node);
            node->left = leftRotate(node->left);
            updateHeight(node);
            cout << "Tree after LR rotation (left part done), before right rotation at " << node->keyword << ":" << endl;
            printLevelOrder(node);
            node = rightRotate(node);
            cout << "Tree after LR rotation (final):" << endl;
            printLevelOrder(node);
        }
        // Left-Left Case
        else {
            cout << "Tree before LL rotation at " << node->keyword << ":" << endl;
            printLevelOrder(original_node);
            node = rightRotate(node);
            cout << "Tree after LL rotation:" << endl;
            printLevelOrder(node);
        }
    }
    // Right Heavy
    else if (balance < -1) {
        // Right-Left Case
        if (calculateBalanceFactor(node->right) > 0) {
            cout << "Tree before RL rotation (right part) at " << node->right->keyword << ":" << endl;
            printLevelOrder(original_node);
            node->right = rightRotate(node->right);
            updateHeight(node);
            cout << "Tree after RL rotation (right part done), before left rotation at " << node->keyword << ":" << endl;
            printLevelOrder(node);
            node = leftRotate(node);
            cout << "Tree after RL rotation (final):" << endl;
            printLevelOrder(node);
        }
        // Right-Right Case
        else {
            cout << "Tree before RR rotation at " << node->keyword << ":" << endl;
            printLevelOrder(original_node);
            node = leftRotate(node);
            cout << "Tree after RR rotation:" << endl;
            printLevelOrder(node);
        }
    }

    return node;
}

Node* insert(Node* root, string keyword, string meaning) {
    if (root == nullptr)
        return new Node(keyword, meaning);

    if (keyword < root->keyword)
        root->left = insert(root->left, keyword, meaning);
    else if (keyword > root->keyword)
        root->right = insert(root->right, keyword, meaning);
    else
        return root;

    return balanceTree(root);
}

void printInOrder(Node* root) {
    if (root != nullptr) {
        printInOrder(root->left);
        cout << root->keyword << " (" << calculateBalanceFactor(root) << ") " << root->meaning << endl;
        printInOrder(root->right);
    }
}

void printReverseInOrder(Node* root) {
    if (root != nullptr) {
        printReverseInOrder(root->right);
        cout << root->keyword << " (" << calculateBalanceFactor(root) << ") " << root->meaning << endl;
        printReverseInOrder(root->left);
    }
}

// Function to print the tree level by level
void printLevelOrder(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty." << endl;
        return;
    }

    queue<Node*> q;
    q.push(root);

    cout << "Level Order Traversal:" << endl;
    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; ++i) {
            Node* current = q.front();
            q.pop();

            if (current != nullptr) {
                cout << current->keyword << "(" << calculateBalanceFactor(current) << ") ";
                q.push(current->left);
                q.push(current->right);
            } else {
                cout << "null ";
            }
        }
        cout << endl;
    }
    cout << "------------------------" << endl;
}

Node* deleteKeyword(Node* root, string keyword) {
    if (root == nullptr)
        return root;

    if (keyword < root->keyword)
        root->left = deleteKeyword(root->left, keyword);
    else if (keyword > root->keyword)
        root->right = deleteKeyword(root->right, keyword);
    else {
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = findMinNode(root->right);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            root->right = deleteKeyword(root->right, temp->keyword);
        }
    }

    if (root == nullptr)
        return root;

    return balanceTree(root);
}

string search(Node* root, string keyword, int& comparisons) {
    Node* current = root;
    comparisons = 0;
    while (current != nullptr) {
        comparisons++; // Count this comparison
        if (keyword == current->keyword) {
            return current->meaning;
        } else if (keyword < current->keyword) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return "Keyword not found.";
}

void updateMeaning(Node* root, string keyword, string newMeaning) {
    Node* current = root;
    while (current != nullptr) {
        if (keyword == current->keyword) {
            current->meaning = newMeaning;
            cout << "Meaning updated." << endl;
            return;
        } else if (keyword < current->keyword) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    cout << "Keyword not found." << endl;
}

int main() {
    Node* root = nullptr;
    string keyword, meaning, newMeaning;
    int comparisons = 0; // Initialize here
    char addMore = 'y';

    while (true) {
        cout << "\n==== AVL Dictionary Menu ====\n";
        cout << "\n1. Add new keyword and meaning\n";
        cout << "2. Print all entries in ascending order\n";
        cout << "3. Print all entries in descending order\n";
        cout << "4. Delete a keyword from dictionary\n";
        cout << "5. Search a keyword\n";
        cout << "6. Update meaning of a keyword\n";
        cout << "7. Get Tree Height\n";
        cout << "8. Display Tree Level Order\n";
        cout << "9. Exit program\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                addMore = 'y';
                while (addMore == 'y' || addMore == 'Y') {
                    cout << "Enter keyword: ";
                    cin >> keyword;
                    cout << "Enter meaning: ";
                    cin.ignore();
                    getline(cin, meaning);

                    rotation_occurred = false;
                    Node* old_root = root; // Keep track if it's the very first node
                    int dummy_comps_before;
                    string meaning_before = search(root, keyword, dummy_comps_before); // Check if exists before

                    root = insert(root, keyword, meaning);
                    printLevelOrder(root);

                    // Provide feedback based on rotation or if it was a new node vs duplicate
                    if (rotation_occurred) {
                        cout << "Keyword '" << keyword << "' inserted/processed (rotation occurred)." << endl;
                    } else {
                        // Check if it was actually inserted or was a duplicate
                        if (meaning_before == "Keyword not found.") { 
                             cout << "Keyword '" << keyword << "' inserted. Tree remains balanced." << endl;
                        } else {
                             cout << "Keyword '" << keyword << "' already exists. No changes made." << endl;
                        }
                    }
                    cout << "Add more keywords? (y/n): ";
                    cin >> addMore;
                }
                break;
            case 2:
                if (root == nullptr)
                    cout << "No entries to display." << endl;
                else
                    printInOrder(root);
                break;
            case 3:
                if (root == nullptr)
                    cout << "No entries to display." << endl;
                else
                    printReverseInOrder(root);
                break;
            case 4:
                if (root == nullptr)
                    cout << "No entries to delete." << endl;
                else {
                    cout << "Enter keyword to delete: ";
                    cin >> keyword;
                    int dummy_comparisons;
                    string search_result = search(root, keyword, dummy_comparisons);

                    if (search_result != "Keyword not found.") {
                        rotation_occurred = false;
                        root = deleteKeyword(root, keyword);
                        cout << "Keyword '" << keyword << "' deleted." << endl;
                        if (!rotation_occurred) {
                            cout << "Tree remains balanced." << endl;
                        }
                    } else {
                        cout << "Keyword not found, cannot delete." << endl;
                    }
                }
                break;
            case 5:
                if (root == nullptr)
                    cout << "Dictionary is empty." << endl;
                else {
                    cout << "Enter keyword to search: ";
                    cin >> keyword;
                    comparisons = 0; 
                    string result = search(root, keyword, comparisons);
                    cout << result << " (Comparisons: " << comparisons << ")" << endl;
                }
                break;
            case 6:
                if (root == nullptr)
                    cout << "Dictionary is empty." << endl;
                else {
                    cout << "Enter keyword to update: ";
                    cin >> keyword;
                    cout << "Enter new meaning: ";
                    cin.ignore();
                    getline(cin, newMeaning);
                    updateMeaning(root, keyword, newMeaning);
                }
                break;
            case 7:
                cout << "Tree Height: " << getHeight(root) << endl;
                break;
            case 8:
                cout << "Current Tree State:" << endl;
                printLevelOrder(root);
                break;
            case 9:
                return 0;
            default:
                cout << "Invalid choice. Please choose a valid option." << endl;
        }
    }
}
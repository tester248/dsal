#include <iostream>
#include <algorithm> 
#include <queue>     
#include <climits>    
using namespace std;

struct Node {
    string keyword, meaning;
    Node* left;
    Node* right;
    int height;

    Node(string key, string m)
    {
        keyword = key;
        meaning = m;
        left = right = nullptr;
        height = 1; 
    }
};

class AVLTree {
public:
    Node* root = nullptr;
    AVLTree(){
        root = nullptr;
    }
    
    int getHeight(Node* node) {
        if (node == nullptr) {
            return 0; 
        }
        return node->height;
    }

    void updateHeight(Node* node) {
        if (node != nullptr) {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }

    int calculateBalanceFactor(Node* node) {
        if (node == nullptr) {
            return 0; 
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rightRotate(Node* y) {
        cout << "Performing Right Rotation at node: " << y->keyword << endl;
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y); // Update y first (now child)
        updateHeight(x); // Update x last (new root)

        return x;
    }

    Node* leftRotate(Node* x) {
        cout << "Performing Left Rotation at node: " << x->keyword << endl;
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x); // Update x first (now child)
        updateHeight(y); // Update y last (new root)

        return y;
    }

    Node* findMinNode(Node* node) {
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* balanceTree(Node* node) {
        if (node == nullptr) {
            return node;
        }

        updateHeight(node);
        int balance = calculateBalanceFactor(node);

        // Left Heavy Cases
        if (balance > 1) {
            // Left-Right Case
            if (calculateBalanceFactor(node->left) < 0) {
                cout << "LR rotation needed at " << node->keyword << endl;
                node->left = leftRotate(node->left);
            }
            // Left-Left Case (or after LR's first step)
             cout << "LL rotation needed at " << node->keyword << endl;
            return rightRotate(node);
        }
        // Right Heavy Cases
        else if (balance < -1) {
            // Right-Left Case
            if (calculateBalanceFactor(node->right) > 0) {
                 cout << "RL rotation needed at " << node->keyword << endl;
                node->right = rightRotate(node->right);
            }
            // Right-Right Case (or after RL's first step)
             cout << "RR rotation needed at " << node->keyword << endl;
            return leftRotate(node);
        }
        return node;
    }

    Node* insert(Node* node, const string& keyword, const string& meaning, bool& inserted) {
        if (node == nullptr) {
            inserted = true;
            return new Node(keyword, meaning);
        }

        if (keyword < node->keyword) {
            node->left = insert(node->left, keyword, meaning, inserted);
        } else if (keyword > node->keyword) {
            node->right = insert(node->right, keyword, meaning, inserted);
        } else {
            cout << "Keyword '" << keyword << "' already exists. Use update option." << endl;
            inserted = false;
            return node;
        }

        if (!inserted) {
            return node;
        }

        return balanceTree(node);
    }

    Node* remove(Node* node, const string& keyword, bool& deleted) {
        if (node == nullptr) {
            deleted = false;
            return node;
        }

        if (keyword < node->keyword) {
            node->left = remove(node->left, keyword, deleted);
        } else if (keyword > node->keyword) {
            node->right = remove(node->right, keyword, deleted);
        } else {
            deleted = true;

            // Case 1 & 2: Node with only one child or no child
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;

                if (temp == nullptr) {
                   temp = node;
                   node = nullptr;
                } else {
                   *node = *temp;
                }
                delete temp;
                temp = nullptr;
            } else {
                // Case 3: Node with two children - replace with inorder successor
                Node* temp = findMinNode(node->right);
                node->keyword = temp->keyword;
                node->meaning = temp->meaning;

                bool dummy_deleted = true;
                node->right = remove(node->right, temp->keyword, dummy_deleted);
            }
        }

        if (node == nullptr) {
            return node;
        }

        if (deleted) {
             return balanceTree(node);
        } else {
             return node;
        }
    }

    void printInOrder(Node* node) {
        if (node != nullptr) {
            printInOrder(node->left);
            cout << node->keyword << " (BF: " << calculateBalanceFactor(node) << ") : " << node->meaning << endl;
            printInOrder(node->right);
        }
    }

    void printReverseInOrder(Node* node) {
         if (node != nullptr) {
            printReverseInOrder(node->right);
            cout << node->keyword << " (BF: " << calculateBalanceFactor(node) << ") : " << node->meaning << endl;
            printReverseInOrder(node->left);
        }
    }

    Node* findNode(const string& keyword) {
         Node* current = root;
         while (current != nullptr) {
             if (keyword == current->keyword) {
                 return current;
             } else if (keyword < current->keyword) {
                 current = current->left;
             } else {
                 current = current->right;
             }
         }
         return nullptr;
    }

    string search(const string& keyword, int& comparisons) {
        Node* current = root;
        comparisons = 0;
        while (current != nullptr) {
            comparisons++;
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

    bool updateMeaning(const string& keyword, const string& newMeaning) {
        Node* node = findNode(keyword);
        if (node != nullptr) {
            node->meaning = newMeaning;
            return true;
        }
        return false;
    }

    void printLevelOrder() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }

        queue<Node*> q;
        q.push(root);
        int level = 0;

        cout << "--- Level Order Traversal ---" << endl;
        while (!q.empty()) {
            int levelSize = q.size();
            cout << "Level " << level << ": ";
            bool level_has_nodes = false;
            for (int i = 0; i < levelSize; ++i) {
                Node* current = q.front();
                q.pop();

                if (current != nullptr) {
                    cout << current->keyword << "(BF:" << calculateBalanceFactor(current) << ") ";
                    level_has_nodes = true;
                    q.push(current->left);
                    q.push(current->right);
                } else {
                     cout << "null ";
                }
            }
            cout << endl;
            
            // Check if remaining nodes are all null
            bool all_null = true;
            queue<Node*> temp_q = q;
            while (!temp_q.empty()) {
                if (temp_q.front() != nullptr) {
                    all_null = false;
                    break;
                }
                temp_q.pop();
            }
            if (all_null) break;

            level++;
        }
        cout << "-----------------------------" << endl;
    }

    int getTreeHeight() {
        return getHeight(root);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

};

int main() {
    AVLTree dictionary;
    string keyword, meaning, newMeaning;
    int comparisons = 0;
    char addMore;
    int choice;
    bool inserted, deleted;

    while (true) {
        cout << "\n==== AVL Dictionary Menu ====\n";
        cout << "1. Add new keyword(s)\n";
        cout << "2. Print Ascending\n";
        cout << "3. Print Descending\n";
        cout << "4. Delete a keyword\n";
        cout << "5. Search a keyword\n";
        cout << "6. Update meaning\n";
        cout << "7. Get Tree Height\n";
        cout << "8. Display Tree Level Order\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
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

                    inserted = false;
                    dictionary.root = dictionary.insert(dictionary.root, keyword, meaning, inserted);
                    if (inserted) {
                        cout << "Keyword '" << keyword << "' inserted." << endl;
                    }

                    dictionary.printLevelOrder();

                    cout << "Add more keywords? (y/n): ";
                    cin >> addMore;
                }
                break;
            case 2:
                if (dictionary.isEmpty()) {
                    cout << "Dictionary is empty." << endl;
                } else {
                    cout << "--- Dictionary Entries (Ascending) ---" << endl;
                    dictionary.printInOrder(dictionary.root);
                    cout << "--------------------------------------" << endl;
                }
                break;
            case 3:
                if (dictionary.isEmpty()) {
                    cout << "Dictionary is empty." << endl;
                } else {
                    cout << "--- Dictionary Entries (Descending) ---" << endl;
                    dictionary.printReverseInOrder(dictionary.root);
                    cout << "---------------------------------------" << endl;
                }
                break;
            case 4:
                if (dictionary.isEmpty()) {
                    cout << "Dictionary is empty. Cannot delete." << endl;
                } else {
                    cout << "Enter keyword to delete: ";
                    cin >> keyword;
                    deleted = false;
                    dictionary.root = dictionary.remove(dictionary.root, keyword, deleted);
                    if (deleted) {
                        cout << "Keyword '" << keyword << "' deleted." << endl;
                        dictionary.printLevelOrder();
                    } else {
                        cout << "Keyword '" << keyword << "' not found, cannot delete." << endl;
                    }
                }
                break;
            case 5:
                 if (dictionary.isEmpty()) {
                     cout << "Dictionary is empty." << endl;
                } else {
                    cout << "Enter keyword to search: ";
                    cin >> keyword;
                    comparisons = 0;
                    string result = dictionary.search(keyword, comparisons);
                    if (result == "Keyword not found.") {
                         cout << "Keyword '" << keyword << "' not found. (Comparisons: " << comparisons << ")" << endl;
                    } else {
                         cout << "Meaning: " << result << " (Comparisons: " << comparisons << ")" << endl;
                    }
                }
                break;
            case 6:
                 if (dictionary.isEmpty()) {
                     cout << "Dictionary is empty." << endl;
                } else {
                    cout << "Enter keyword to update: ";
                    cin >> keyword;
                    cout << "Enter new meaning: ";
                    cin.ignore();
                    getline(cin, newMeaning);
                    if (dictionary.updateMeaning(keyword, newMeaning)) {
                        cout << "Meaning updated successfully." << endl;
                    } else {
                        cout << "Keyword '" << keyword << "' not found, cannot update." << endl;
                    }
                }
                break;
            case 7:
                cout << "Tree Height: " << dictionary.getTreeHeight() << endl;
                break;
            case 8:
                cout << "Current Tree State:" << endl;
                dictionary.printLevelOrder();
                break;
            case 9:
                 cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please choose a valid option." << endl;
        }
    }
}
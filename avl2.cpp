#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
    string key, meaning;
    Node* left;
    Node* right;
    int height;

    Node(string k, string m) : key(k), meaning(m), left(nullptr), right(nullptr), height(1) {}
};

Node* insert(Node* node, string key, string meaning);
Node* deleteNode(Node* root, string key);
void updateMeaning(Node* root, string key, string newMeaning);
void displayAscending(Node* root);
void displayDescending(Node* root);
void printTreeStructure(Node* root, int level = 0, char branch = ' ');

int getHeight(Node* node) {
    return node ? node->height : 0;
}

int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

Node* insert(Node* node, string key, string meaning) {
    if (!node) return new Node(key, meaning);
    if (key < node->key)
        node->left = insert(node->left, key, meaning);
    else if (key > node->key)
        node->right = insert(node->right, key, meaning);
    else
        return node;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key) return rightRotate(node);
    if (balance < -1 && key > node->right->key) return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left) current = current->left;
    return current;
}

Node* deleteNode(Node* root, string key) {
    if (!root) return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->meaning = temp->meaning;
        root->right = deleteNode(root->right, temp->key);
    }
    if (!root) return root;
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void displayAscending(Node* root) {
    if (root) {
        displayAscending(root->left);
        cout << root->key << ": " << root->meaning << endl;
        displayAscending(root->right);
    }
}

void displayDescending(Node* root) {
    if (root) {
        displayDescending(root->right);
        cout << root->key << ": " << root->meaning << endl;
        displayDescending(root->left);
    }
}

void updateMeaning(Node* root, string key, string newMeaning) {
    while (root) {
        if (key == root->key) {
            root->meaning = newMeaning;
            cout << "Meaning updated." << endl;
            return;
        } else if (key < root->key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    cout << "Keyword not found." << endl;
}

int maxComparisons(Node* root) {
    return root ? getHeight(root) : 0;
}

void printTreeStructure(Node* root, int level, char branch) {
    if (!root) return;
    if (level > 0) {
        for (int i = 0; i < level - 1; i++) cout << "�   ";
        cout << (branch == 'L' ? "[L]+-- " : "[R]+-- ");
    }
    cout << root->key << " (" << getBalance(root) << ")" << endl;
    printTreeStructure(root->left, level + 1, 'L');
    printTreeStructure(root->right, level + 1, 'R');
}

int main() {
    Node* root = nullptr;
    int choice;
    string key, meaning;

    while (true) {
        cout << "\n[ 1 = Insert node and display tree ]\n[ 2 = Delete node and display tree ]\n[ 3 = Update meaning ]\n[ 4 = Display ascending ]\n[ 5 = Display descending ]\n[ 6 = Max comparisons to find any node ]\n[ 7 = Exit ]\n\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                getline(cin, key);
                cout << "Enter meaning: ";
                getline(cin, meaning);
                root = insert(root, key, meaning);
                cout << "\nNode inserted. \n";
                
                cout << "\nCurrent tree structure:\n";
				printTreeStructure(root);
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                getline(cin, key);
                root = deleteNode(root, key);
                cout << "\nNode deleted. \n";
                
                cout << "\nCurrent tree structure:\n";
				printTreeStructure(root);    
                break;
            case 3:
                cout << "Enter keyword to update: ";
                getline(cin, key);
                cout << "Enter new meaning: ";
                getline(cin, meaning);
                updateMeaning(root, key, meaning);
                break;
            case 4:
                cout << "\nDictionary in Ascending Order:\n";
                displayAscending(root);
                break;
            case 5:
                cout << "\nDictionary in Descending Order:\n";
                displayDescending(root);
                break;
            case 6:
			    cout << "\nMaximum comparisons required to find any node: " << maxComparisons(root) << endl;
			    break;
            case 7:
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}

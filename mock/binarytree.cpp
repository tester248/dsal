#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int val)
    {
        data = val;
        left = right = nullptr;
    }
};


Node* insert(Node* root) {
    int val;
    cout << "\nEnter value of node: ";
    cin >> val;
    if (root == nullptr) {
        cout << "\nRoot node created" << endl;
        return new Node(val);
    }
    Node* curr = root;
    while (true) {
        if (val < curr->data) {
            if (curr->left == nullptr) {
                curr->left = new Node(val);
                cout << "\nLeft node Inserted";
                break;
            } else {
                curr = curr->left;
            }
        } else if (val > curr->data) {
            if (curr->right == nullptr) {
                curr->right = new Node(val);
                cout << "\nRight node inserted";
                break;
            } else {
                curr = curr->right;
            }
        } else {
            cout << "\nEntry repeated";
            break;
        }
    }
    return root;
}

void display(Node* temp) {
    if (temp != nullptr) {
        display(temp->left);
        cout << "\t" << temp->data << " ";
        display(temp->right);
    }
}

bool search(Node* root, int key) {
    Node* temp = root;
    while (temp != nullptr) {
        if (key < temp->data) {
            temp = temp->left;
        } else if (key > temp->data) {
            temp = temp->right;
        } else {
            cout << "\nValue " << key << " is present";
            return true;
        }
    }
    return false;
}

// Height of tree (longest path from root)
int height(Node* node) {
    if (node == nullptr)
        return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return max(leftHeight, rightHeight) + 1;
}

// Find minimum value in BST
int findMin(Node* node) {
    if (node == nullptr) {
        cout << "\n\tTree is empty";
        return -1;
    }
    while (node->left != nullptr) {
        node = node->left;
    }
    return node->data;
}

// Mirror the tree
void mirror(Node* node) {
    if (node == nullptr)
        return;
    swap(node->left, node->right);
    mirror(node->left);
    mirror(node->right);
}

int main() {
    Node* root = nullptr;
    int ch, val;
    do {
        cout << "\n====BST MENU====";
        cout << "\n1.Insert";
        cout << "\n2.Display";
        cout << "\n3.Search the node";
        cout << "\n4.Height of the tree";
        cout << "\n5.Minimum value in the tree";
        cout << "\n6.Mirror the tree";
        cout << "\n7.Exit";
        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch) {
        case 1:
            root = insert(root);
            cout << "\n";
            break;
        case 2:
            cout << "\nTREE:\n";
            if (root == nullptr)
                cout << "\nTree is empty";
            else
                display(root);
            cout << "\n";
            break;
        case 3:
            cout << "\nEnter the value to search: ";
            cin >> val;
            if (!search(root, val)) {
                cout << "\nValue is absent";
            }
            cout << "\n";
            break;
        case 4:
            cout << "\nHeight of the tree: " << height(root);
            cout << "\n";
            break;
        case 5:
            val = findMin(root);
            if (val != -1)
                cout << "\nMinimum value in the tree: " << val;
            cout << "\n";
            break;
        case 6:
            mirror(root);
            cout << "\nTree mirrored successfully";
            cout << "\n";
            break;
        case 7:
            cout << "\nExiting the program...";
            break;
        default:
            cout << "\nINVALID INPUT";
            cout << "\n";
            break;
        }
    } while (ch != 7);
    return 0;
}

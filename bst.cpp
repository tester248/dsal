#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, int data) {
        if (node == nullptr) {
            return new Node(data);
        }
        if (data < node->data) {
            node->left = insert(node->left, data);
        } else {
            node->right = insert(node->right, data);
        }
        return node;
    }

    int findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node->data;
    }

    int findMaxDepth(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftDepth = findMaxDepth(node->left);
        int rightDepth = findMaxDepth(node->right);
        return max(leftDepth, rightDepth) + 1;
    }

    Node* swapChildren(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        swap(node->left, node->right);
        swapChildren(node->left);
        swapChildren(node->right);
        return node;
    }

    bool search(Node* node, int data) {
        if (node == nullptr) {
            return false;
        }
        if (node->data == data) {
            return true;
        }
        if (data < node->data) {
            return search(node->left, data);
        } else {
            return search(node->right, data);
        }
    }

public:
    BST() : root(nullptr) {}

    void insert(int data) {
        root = insert(root, data);
    }

    int findMin() {
        if (root == nullptr) {
            throw runtime_error("Tree is empty");
        }
        return findMin(root);
    }

    int findMaxDepth() {
        return findMaxDepth(root);
    }

    void swapChildren() {
        root = swapChildren(root);
    }

    bool search(int data) {
        return search(root, data);
    }

    void inorder(Node* node) {
        if (node == nullptr) {
            return;
        }
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void display() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    BST tree;
    int values[] = {50, 30, 20, 40, 70, 60, 80};
    for (int val : values) {
        tree.insert(val);
    }

    cout << "Inorder traversal of the BST: ";
    tree.display();

    tree.insert(25);
    cout << "Inorder traversal after inserting 25: ";
    tree.display();

    cout << "Number of nodes in longest path from root: " << tree.findMaxDepth() << endl;
    cout << "Minimum data value found in the tree: " << tree.findMin() << endl;

    tree.swapChildren();
    cout << "Inorder traversal after swapping children: ";
    tree.display();

    int searchValue = 40;
    cout << "Search for value " << searchValue << ": " << (tree.search(searchValue) ? "Found" : "Not Found") << endl;

    return 0;
}
#include<iostream>
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

Node* insert(Node* root, int val)
{
    if(root == nullptr){
        cout <<endl<< "Root node created" <<endl;
        return new Node(val);
    }
    Node *current = root;
    while (true){
        if(val < current->data){
            if(current->left == nullptr){
                current->left = new Node(val);
                cout <<endl<< "Left Node Inserted" <<endl;
                break;
            } else {
                current = current -> left;
            }
        } else if (val > current->data){
            if(current->right == nullptr){
                current->right = new Node(val);
                cout <<endl<< "Right Node Inserted" <<endl;
                break;
            } else {
                current = current -> right;
            }
        } else {
            cout << endl << "Entry repeated" <<endl;
            break;
        }
    }
    return root;
}

int height(Node* node) {
    if (node == nullptr)
        return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return max(leftHeight, rightHeight) + 1;
}

int findMin(Node* node) {
    if (node == nullptr){
        cout <<endl<< "Tree is empty" <<endl;
        return -1;
    }
    while (node->left != nullptr) {
        node = node->left;
    }
    return node->data;
}

void mirror(Node* node) {
    if (node == nullptr)
        return;
    swap(node->left, node->right);
    mirror(node->left);
    mirror(node->right);
}

bool search(Node* root, int key) {
    Node* current = root;
    while  (current != nullptr) {
        if( key < current -> data) {
            current = current -> left;
        } else if (key > current -> data) {
            current = current -> right;
        } else {
            return true;
        }
    }
    return false;
}

void display(Node* temp) {
    if (temp != nullptr) {
        display(temp->left);
        cout << "\t" << temp->data << " ";
        display(temp->right);
    }
}

// // Level-order (layer-wise) display function
// void displayLevelOrder(Node* root) {
//     if (root == nullptr) {
//         cout << "\nTree is empty";
//         return;
//     }
    
//     // Using a queue to process nodes level by level
//     queue<Node*> q;
//     q.push(root);
    
//     while (!q.empty()) {
//         int levelSize = q.size(); // Number of nodes at current level
//         cout << "\nLevel: ";
        
//         // Process all nodes at current level
//         for (int i = 0; i < levelSize; i++) {
//             Node* current = q.front();
//             q.pop();
            
//             cout << current->data << " ";
            
//             // Enqueue children for next level
//             if (current->left != nullptr)
//                 q.push(current->left);
//             if (current->right != nullptr)
//                 q.push(current->right);
//         }
//     }
// }

int main() {
    Node* root = nullptr;
    int ch, val;
    while (true){
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
                cout << "Enter value to insert: ";
                cin >> val;
                root = insert(root, val);
                break;
            case 2:
                cout << "\nTREE:\n";
                if (root == nullptr)
                    cout << "\nTree is empty";
                else
                    display(root);
                break;
            case 3:
                cout << "Enter the value to search: ";
                cin >> val;
                if (!search(root, val)) {
                    cout << "\nValue is absent";
                } else {
                    cout << "\nValue is present";
                }
                break;
            case 4:
                cout << "\nHeight of the tree: " << height(root);
                break;
            case 5:
                val = findMin(root);
                if (val != -1)
                    cout << "\nMinimum value in the tree: " << val;
                break;
            case 6:
                mirror(root);
                cout << "\nTree mirrored successfully";
                break;
            case 7:
                cout << "\nExiting the program...";
                return 0;
            default:
                cout << "\nINVALID INPUT";
                break;
        }
    }
}
#include <iostream>
#include <algorithm>
using namespace std;
const int MAX_SIZE = 100; 

struct Node{
    char data;
    Node* left;
    Node* right;
    Node(char ch){
        data = ch;
        left = right = nullptr;
    }
};

class Stack {
private:
    Node* arr[MAX_SIZE];
    int top;
public:
    Stack() {
        top = -1; 
    }
    void push(Node* newNode) {
        if (top >= MAX_SIZE - 1) {
            cout << "Stack Overflow" << endl;
        }
        arr[++top] = newNode;
    }
    Node* pop() {
        if (top < 0) {
            cout << "Stack Underflow" << endl;
            return nullptr; 
        }
        return arr[top--];
    }

    bool isEmpty() {
        return (top < 0);
    }

    Node* peek() {
        if (top < 0) {
            cout << "Stack is Empty" << endl;
            return nullptr; 
        }
        return arr[top];
    }
};

class ExpressionTree {
private:
    Node* root;
public:
    ExpressionTree() {
        root = nullptr;
    }

    Node* constructTree(string prefix)
    {
        Stack stack;
        for (int i = prefix.size() -1; i >= 0; i--) {
            if (isalnum(prefix[i])) {
                Node* newNode = new Node(prefix[i]);
                stack.push(newNode);
            } else {
                Node* newNode = new Node(prefix[i]);
                newNode->left = stack.pop();
                newNode->right = stack.pop();
                stack.push(newNode);
            }
        }
        return stack.pop();
    }

    // postorder traversal (non recursive) using string reversal
    void postOrder(Node* root)
    {
        if (root == nullptr) {
            return;
        }
        Stack stack;
        string postOrder = "";
        stack.push(root);
        while (!stack.isEmpty()) {
            Node* temp = stack.peek();
            stack.pop();
            postOrder += temp->data;
            if (temp->left) {
                stack.push(temp->left);
            }
            if (temp->right) {
                stack.push(temp->right);
            }
        }
        
        //string reversal
        reverse(postOrder.begin(), postOrder.end());
        cout << "Postorder traversal: " << postOrder << endl;
    }

    //delete tree (non recursive)
    void deleteTree(Node* root)
    {
        if (root == nullptr) {
            return;
        }
        Stack stack;
        stack.push(root);
        while (!stack.isEmpty()) {
            Node* temp = stack.peek();
            stack.pop();
            if (temp->left) {
                stack.push(temp->left);
            }
            if (temp->right) {
                stack.push(temp->right);
            }
            delete temp;
        }
    }

};

int main() {
    ExpressionTree tree;
    string prefix;
    int choice;
    Node* root = nullptr;

    do {
        cout << "\nMenu:\n";
        cout << "1. Construct Expression Tree\n";
        cout << "2. Postorder Traversal\n";
        cout << "3. Delete Tree\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter prefix expression: ";
                cin >> prefix;
                if(root != nullptr)
                {
                    tree.deleteTree(root);
                }
                root = tree.constructTree(prefix);
                if(root != nullptr){
                    cout << "Expression tree constructed.\n";
                }
                break;
            case 2:
                if (root == nullptr) {
                    cout << "Tree is empty. Construct tree first.\n";
                } else {
                    tree.postOrder(root);
                }
                break;
            case 3:
                if (root == nullptr) {
                    cout << "Tree is empty.\n";
                } else {
                    tree.deleteTree(root);
                    root = nullptr;
                    cout << "Tree deleted.\n";
                }
                break;
            case 4:
                if(root != nullptr){
                    tree.deleteTree(root);
                }
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}

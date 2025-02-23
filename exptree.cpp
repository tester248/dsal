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
    string prefix = "+--a*bc/def";
    Node* root = tree.constructTree(prefix);
    tree.postOrder(root);
    tree.deleteTree(root);
    cout<<"Tree deleted"<<endl;
    return 0;
}

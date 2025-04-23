#include<iostream>
#include<algorithm>
//+--a*bc/def
using namespace std;
const int max_size = 100;

struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char ch) {
        data = ch;
        left = right = nullptr;
    }
};

class Stack
{
    private:
        Node *arr[max_size];
        int top;
    public:
        Stack() {
            top = -1;
        }
        void push(Node* newNode) {
            if (top >= max_size -1) {
                cout << "Stack Overflow" << endl;
            } else {
                arr[++top] = newNode;
            }
        }
        Node* pop() {
            if (top < 0) {
                cout << "Stack Underflow" << endl;
                return nullptr;
            } else {
                return arr[top--];
            }
        }
        bool isEmpty() {
            return (top < 0);
        }
        Node* peek() {
            if (top < 0) {
                cout << "Stack is Empty" << endl;
                return nullptr;
            } else {
                return arr[top];
            }
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
            Stack s;
            for(int i = prefix.size() - 1; i >= 0; i--)
            {
                if(isalnum(prefix[i]))
                {
                    Node* newNode = new Node(prefix[i]);
                    s.push(newNode);
                } else {
                    Node* newNode = new Node(prefix[i]);
                    newNode->left = s.pop();
                    newNode->right = s.pop();
                    s.push(newNode);
                }
            }
            return s.pop();
        }

        void postOrder(Node* root)
        {
            if (root == nullptr)
                cout << "Tree is empty." << endl;
                return;
            Stack s;
            string postOrder = "";
            s.push(root);
            while (!s.isEmpty()) {
                Node* temp = s.peek();
                s.pop();
                postOrder += temp->data;
                if (temp->left) {
                    s.push(temp->left);
                }
                if (temp->right) {
                    s.push(temp->right);
                }
            }
            reverse(postOrder.begin(), postOrder.end());
            cout << "Postorder traversal: " << postOrder << endl;
        }

        void deleteTree(Node* root)
        {
            if (root == nullptr) {
                cout<< "Tree is already empty." << endl;
                return;
            }
            Stack s;
            s.push(root);
            while (!s.isEmpty()) {
                Node* temp = s.peek();
                s.pop();
                if (temp->left) {
                    s.push(temp->left);
                }
                if (temp->right) {
                    s.push(temp->right);
                }
                delete temp;
            }
            cout << "Tree deleted successfully." << endl;
        }
};

int main()
{
    ExpressionTree tree;
    string prefix;
    int choice;
    Node* root = nullptr;

    do{
        cout <<endl<< "==Expression Tree Menu=="<<endl;
        cout << "1. Construct Tree from Prefix Expression" << endl;
        cout << "2. Postorder Traversal" << endl;
        cout << "3. Delete Tree" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice) {
            case 1:
                cout << "Enter prefix expression: ";
                cin >> prefix;
                root = tree.constructTree(prefix);
                cout << "Expression Tree constructed." << endl;
                break;
            case 2:
                tree.postOrder(root);
                break;
            case 3:
                tree.deleteTree(root);
                root = nullptr;
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }while(choice != 4);
}

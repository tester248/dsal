#include<iostream>
#include<algorithm>
#include<stack>
//+--a*bc/def 
using namespace std;

struct Node {
    char data;
    Node *left, *right;
    Node(char ch) {
        data = ch;
        left = right = nullptr;
    }
};

class ExpressionTree {
    private:
        Node* root;
    public:
        ExpressionTree(){
            root = nullptr;
        }

        void constructTree(string prefix){
            stack<Node*> s;
            for (int i = prefix.length() - 1; i >= 0; i--) {
                if(isalnum(prefix[i]))
                    s.push(new Node(prefix[i]));
                else {
                    Node *newNode = new Node(prefix[i]);
                    newNode->left = s.top(); s.pop();
                    newNode->right = s.top(); s.pop();
                    s.push(newNode);
                }
            }
            root = s.top();
        }

        void postOrder(){
            if (root == nullptr){
                cout << "Tree is empty." << endl;
                return;
            }
            stack<Node*> s;
            string postorder = "";
            s.push(root);
            while (!s.empty()){
                Node* temp = s.top();
                s.pop();
                postorder += temp->data;
                if (temp->left)
                    s.push(temp->left);
                if (temp->right)
                    s.push(temp->right);
            }
            reverse(postorder.begin(), postorder.end());
            cout << "Postorder Traversal: " << postorder << endl;
        }

        void deleteTree(){
            if (root == nullptr){
                cout << "Tree is already empty." << endl;
                return;
            }
            stack<Node*> s;
            s.push(root);
            while (!s.empty()){
                Node *temp = s.top();
                s.pop();
                if(temp->left)
                    s.push(temp->left);
                if(temp->right)
                    s.push(temp->right);
                delete temp;
            }
            cout << "Tree deleted successfully." << endl;
        }
};

//menu driven
int main() {
    ExpressionTree tree;
    string prefix;
    int choice;
    do {
        cout << endl <<" ===Expression Tree Menu===";
        cout << "\n1. Construct Expression Tree from Prefix Expression";
        cout << "\n2. Postorder Traversal of the Tree";
        cout << "\n3. Delete the Tree";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter prefix expression: ";
                cin >> prefix;
                tree.constructTree(prefix);
                break;
            case 2:
                tree.postOrder();
                break;
            case 3:
                tree.deleteTree();
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);
    return 0;
}


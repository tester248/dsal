#include <iostream>
#include <string>

using namespace std;

struct Node {
public:
    string keyword;      
    string meaning;       
    Node* left;          
    Node* right;         
    Node(string key, string m) {
        keyword = key;
        meaning = m;
        left = nullptr;
        right = nullptr;
    }
};


Node* insert(Node* root, string keyword, string meaning) 
{
    if (root == nullptr)
        return new Node(keyword, meaning);
    else 
    {
        if (keyword < root->keyword)
            root->left = insert(root->left, keyword, meaning);
        else
            root->right = insert(root->right, keyword, meaning);
        return root;
    }
}

//ascending
void printInOrder(Node* root) {
    if (root != nullptr) {
        printInOrder(root->left);
        cout << root->keyword << " " << root->meaning << endl;
        printInOrder(root->right);
    }
}

//decending
void printReverseInOrder(Node* root) {
    if (root != nullptr) {
        printReverseInOrder(root->right);
        cout << root->keyword << " " << root->meaning << endl;
        printReverseInOrder(root->left);
        
    }
}

Node* deleteKeyword(Node* root, string keyword) 
{
    if (root == nullptr) 
        return root;
    if (keyword < root->keyword)
        root->left = deleteKeyword(root->left, keyword);
    else if (keyword > root->keyword)
        root->right = deleteKeyword(root->right, keyword);
    else
    {
        if (root->left == nullptr && root->right == nullptr)//no children
            return nullptr;
        else if (root->left == nullptr)//right child
            return root->right;
        else if (root->right == nullptr)//left child
            return root->left;
        else {
            string minKeyword = " "; // variable to store the minimum keyword in right subtree
            Node* current = root->right;
            while(current->left != nullptr)
                current = current->left; // find the node with minimum value in right subtree

            root->keyword = current->keyword;
            root->meaning = current->meaning;
            root->right = deleteKeyword(root->right, minKeyword);
        }
    }

    return root;
}

int main() {
    Node* root = nullptr; 
    string keyword, meaning;

    while (true) {
        cout << "\n1. Add new keyword and meaning\n";
        cout << "2. Print all entries in ascending order\n";
        cout << "3. Print all entries in descending order\n";
        cout << "4. Delete a keyword from dictionary\n";
        cout << "5. Exit program\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                cin >> keyword;
                cout << "Enter meaning: ";
                cin >> meaning;
                root = insert(root, keyword, meaning);
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
                if(root == nullptr)
                    cout << "No entries to delete." << endl;
                else {
                    cout << "Enter keyword to delete: ";
                    cin >> keyword;
                    root = deleteKeyword(root, keyword);
                }
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice. Please choose a valid option." << endl;
        }
    }

    return 0;
}

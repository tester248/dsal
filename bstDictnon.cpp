#include <iostream>
#include <string>
#include <stack>

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
    Node* newNode = new Node(keyword, meaning);
    if (root == nullptr)
        return newNode;

    Node* current = root;
    Node* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (keyword < current->keyword)
            current = current->left;
        else
            current = current->right;
    }

    if (keyword < parent->keyword)
        parent->left = newNode;
    else
        parent->right = newNode;

    return root;
}

//ascending
void printInOrder(Node* root) {
    if (root == nullptr)
        return;

    stack<Node*> s;
    Node* current = root;

    while (current != nullptr || !s.empty()) {
        while (current != nullptr) {
            s.push(current);
            current = current->left;
        }

        current = s.top();
        s.pop();
        cout << current->keyword << " " << current->meaning << endl;
        current = current->right;
    }
}

//descending
void printReverseInOrder(Node* root) {
    if (root == nullptr)
        return;

    stack<Node*> s;
    Node* current = root;

    while (current != nullptr || !s.empty()) {
        while (current != nullptr) {
            s.push(current);
            current = current->right;
        }

        current = s.top();
        s.pop();
        cout << current->keyword << " " << current->meaning << endl;
        current = current->left;
    }
}

Node* deleteKeyword(Node* root, string keyword) 
{
    if (root == nullptr)
        return root;

    Node* parent = nullptr;
    Node* current = root;

    while (current != nullptr && current->keyword != keyword) {
        parent = current;
        if (keyword < current->keyword)
            current = current->left;
        else
            current = current->right;
    }

    if (current == nullptr)
        return root;

    if (current->left == nullptr || current->right == nullptr) {
        Node* newCurrent;

        if (current->left == nullptr)
            newCurrent = current->right;
        else
            newCurrent = current->left;

        if (parent == nullptr)
            return newCurrent;

        if (current == parent->left)
            parent->left = newCurrent;
        else
            parent->right = newCurrent;

        delete current;
    } else {
        Node* p = nullptr;
        Node* temp;

        temp = current->right;
        while (temp->left != nullptr) {
            p = temp;
            temp = temp->left;
        }

        if (p != nullptr)
            p->left = temp->right;
        else
            current->right = temp->right;

        current->keyword = temp->keyword;
        current->meaning = temp->meaning;

        delete temp;
    }

    return root;
}

int findKeyword(Node* root, string keyword) {
    int comparisons = 0;
    Node* current = root;

    while (current != nullptr) {
        comparisons++;
        if (keyword == current->keyword) {
            cout << "Keyword found: " << current->keyword << " with meaning: " << current->meaning << endl;
            return comparisons;
        } else if (keyword < current->keyword) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    cout << "Keyword not found." << endl;
    return comparisons;
}

int main() {
    Node* root = nullptr; 
    string keyword, meaning;

    while (true) {
        cout << "\n1. Add new keyword and meaning\n";
        cout << "2. Print all entries in ascending order\n";
        cout << "3. Print all entries in descending order\n";
        cout << "4. Delete a keyword from dictionary\n";
        cout << "5. Find a keyword and count comparisons\n";
        cout << "6. Exit program\n";
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
                if(root == nullptr)
                    cout << "No entries to find." << endl;
                else {
                    cout << "Enter keyword to find: ";
                    cin >> keyword;
                    int comparisons = findKeyword(root, keyword);
                    cout << "Number of comparisons: " << comparisons << endl;
                }
                break;
            case 6:
                return 0;
            default:
                cout << "Invalid choice. Please choose a valid option." << endl;
        }
    }

    return 0;
}
#include<iostream>
using namespace std;

struct Node {
    string keyword, meaning;
    Node *left, *right;
    Node(string key, string m) {
        keyword = key;
        meaning = m;
        left = right = nullptr;
    }
};

Node* insert(Node* root, string key, string meaning) {
    if(root == nullptr)
        return new Node(key, meaning);
    if(key < root->keyword)
        root->left = insert(root->left, key, meaning);
    else if(key > root->keyword)
        root->right = insert(root->right, key, meaning);
    return root;
}

Node* findMinNode(Node* node){
    while(node->left != nullptr)
        node = node->left;
    return node;
}

Node* deleteKeyword(Node* root, string key)
{
    if(root == nullptr)
        return root;
    if(key < root->keyword)
        root->left = deleteKeyword(root->left, key);
    else if(key > root->keyword)
        root->right = deleteKeyword(root->right, key);
    else {
        if(root->left == nullptr && root->right == nullptr)
            return nullptr;
        else if(root->left == nullptr)
            return root->right;
        else if(root->right == nullptr)
            return root->left;
        else {
            Node* minNode = findMinNode(root->right);
            root->keyword = minNode->keyword;
            root->meaning = minNode->meaning;
            root->right = deleteKeyword(root->right, minNode->keyword);
        }
    }
    return root;
}



void updateMeaning(Node* root, string key, string newMeaning){
    Node* current = root;
    while(current != nullptr){
        if(current->keyword == key){
            current ->meaning = newMeaning;
            cout << "Meaning updated." << endl;
            return;
        } else if (key < current->keyword){
            current = current->left;
        } else {
            current = current->right;
        }
    }
    cout << "Keyword not found." << endl;
}

//inorder traversal
void ascending(Node* &root){
    if(root != nullptr){
        ascending(root->left);
        cout << root->keyword << " " << root->meaning <<endl;
        ascending(root->right);
    }
}

//reverse inorder traversal
void decending(Node* &root){
    if(root != nullptr){
        decending(root->right);
        cout << root->keyword << " " << root->meaning <<endl;
        decending(root->left);
    }
}

int search(Node* root, string key)
{
    Node* current = root;
    int comparisons = 0;
    while(current != nullptr){
        comparisons++;
        if(key < current->keyword)
            current = current->left;
        else if(key > current->keyword)
            current = current->right;
        else {
            cout << "Keyword found: " << current->keyword << " - " << current->meaning << endl;
            return comparisons;
        }
    }
    return -1;
}

int main() {
    Node* root = nullptr;
    string keyword, meaning, newMeaning;
    char addMore;
    int comparisons;
    while(true){
        cout << "====DICTIONARY====" << endl;
        cout << "1. Add keyword" << endl;
        cout << "2. Display keywords in ascending order" << endl;
        cout << "3. Display keywords in descending order" << endl;
        cout << "4. Delete keyword" << endl;
        cout << "5. Search keyword" << endl;
        cout << "6. Update meaning" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch(choice){
            case 1:
                addMore = 'y';
                while (addMore == 'y' || addMore == 'Y') {
                    cout << "Enter keyword: ";
                    cin >> keyword;
                    cout << "Enter meaning: ";
                    cin.ignore();
                    getline(cin, meaning);
                    root = insert(root, keyword, meaning);
                    cout << "Add more keywords? (y/n): ";
                    cin >> addMore;
                }
            break;
            case 2:
                ascending(root);
                break;
            case 3:
                decending(root);
                break;
            case 4:
                cout << "Enter keyword to delete: ";
                cin >> keyword;
                root = deleteKeyword(root, keyword);
                break;
            case 5:
                cout << "Enter keyword to search: ";
                cin >> keyword;
                comparisons = search(root, keyword);
                if(comparisons == -1)
                    cout << "Keyword not found." << endl;
                else
                    cout << "Comparisons made: " << comparisons << endl;
                break;
            case 6:
                cout << "Enter keyword to update: ";
                cin >> keyword;
                cout << "Enter new meaning: ";
                cin.ignore();
                getline(cin, newMeaning);
                updateMeaning(root, keyword, newMeaning);
                break;
            case 7:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}
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

Node* findMinNode(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

Node* insert(Node* root, string keyword, string meaning) {
    if (root == nullptr)
        return new Node(keyword, meaning);
    else {
        if (keyword < root->keyword)
            root->left = insert(root->left, keyword, meaning);
        else
            root->right = insert(root->right, keyword, meaning);
        return root;
    }
}

void printInOrder(Node* root) {
    if (root != nullptr) {
        printInOrder(root->left);
        cout << root->keyword << " " << root->meaning << endl;
        printInOrder(root->right);
    }
}

void printReverseInOrder(Node* root) {
    if (root != nullptr) {
        printReverseInOrder(root->right);
        cout << root->keyword << " " << root->meaning << endl;
        printReverseInOrder(root->left);
    }
}

Node* deleteKeyword(Node* root, string keyword) {
    if (root == nullptr)
        return root;
    if (keyword < root->keyword)
        root->left = deleteKeyword(root->left, keyword);
    else if (keyword > root->keyword)
        root->right = deleteKeyword(root->right, keyword);
    else {
        if (root->left == nullptr && root->right == nullptr)
            return nullptr;
        else if (root->left == nullptr)
            return root->right;
        else if (root->right == nullptr)
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

string search(Node* root, string keyword, int& comparisons) {
    Node* current = root;
    comparisons = 0;
    while (current != nullptr) {
        comparisons++;
        if (keyword == current->keyword) {
            return current->meaning;
        } else if (keyword < current->keyword) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return "Keyword not found.";
}

void updateMeaning(Node* root, string keyword, string newMeaning) {
    Node* current = root;
    while (current != nullptr) {
        if (keyword == current->keyword) {
            current->meaning = newMeaning;
            cout << "Meaning updated." << endl;
            return;
        } else if (keyword < current->keyword) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    cout << "Keyword not found." << endl;
}

int getHeight(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + max(getHeight(root->left), getHeight(root->right));
}

int main() {
    Node* root = nullptr;
    string keyword, meaning, newMeaning;
    int comparisons;
    char addMore = 'y';

    while (true) {
        cout << "\n==== Dictionary Menu ====\n";
        cout << "\n1. Add new keyword and meaning\n";
        cout << "2. Print all entries in ascending order\n";
        cout << "3. Print all entries in descending order\n";
        cout << "4. Delete a keyword from dictionary\n";
        cout << "5. Search a keyword\n";
        cout << "6. Update meaning of a keyword\n";
        cout << "7. Get maximum comparisons needed\n";
        cout << "8. Exit program\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
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
                if (root == nullptr)
                    cout << "No entries to delete." << endl;
                else {
                    cout << "Enter keyword to delete: ";
                    cin >> keyword;
                    root = deleteKeyword(root, keyword);
                }
                break;
            case 5:
                if (root == nullptr)
                    cout << "Dictionary is empty." << endl;
                else {
                    cout << "Enter keyword to search: ";
                    cin >> keyword;
                    cout << search(root, keyword, comparisons) << " (Comparisons: " << comparisons << ")" << endl;
                }
                break;
            case 6:
                if (root == nullptr)
                    cout << "Dictionary is empty." << endl;
                else {
                    cout << "Enter keyword to update: ";
                    cin >> keyword;
                    cout << "Enter new meaning: ";
                    cin.ignore();
                    getline(cin, newMeaning);
                    updateMeaning(root, keyword, newMeaning);
                }
                break;
            case 7:
                cout << "Maximum comparisons needed: " << getHeight(root) -1 << endl;
                break;
            case 8:
                return 0;
            default:
                cout << "Invalid choice. Please choose a valid option." << endl;
        }
    }
}
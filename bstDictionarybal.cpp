#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
public:
    string keyword;      
    string meaning;       
    Node* left;          
    Node* right;         
    int height; // Height of the node
    Node(string key, string m) {
        keyword = key;
        meaning = m;
        left = nullptr;
        right = nullptr;
        height = 1; // New node is initially added at leaf
    }
};

// Utility function to get the height of the node
int height(Node* N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

// Utility function to get the balance factor of the node
int getBalance(Node* N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

// Right rotate subtree rooted with y
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Left rotate subtree rooted with x
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

Node* insert(Node* root, string keyword, string meaning) {
    if (root == nullptr)
        return new Node(keyword, meaning);

    if (keyword < root->keyword)
        root->left = insert(root->left, keyword, meaning);
    else if (keyword > root->keyword)
        root->right = insert(root->right, keyword, meaning);
    else // Duplicate keywords are not allowed
        return root;

    // Update height of this ancestor node
    root->height = 1 + max(height(root->left), height(root->right));

    // Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && keyword < root->left->keyword)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && keyword > root->right->keyword)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && keyword > root->left->keyword) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && keyword < root->right->keyword) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to update the meaning of a keyword
Node* update(Node* root, string keyword, string newMeaning) {
    if (root == nullptr)
        return nullptr;

    if (keyword < root->keyword)
        root->left = update(root->left, keyword, newMeaning);
    else if (keyword > root->keyword)
        root->right = update(root->right, keyword, newMeaning);
    else
        root->meaning = newMeaning;

    return root;
}

// Function to find the minimum value node
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* deleteKeyword(Node* root, string keyword) {
    if (root == nullptr)
        return root;

    if (keyword < root->keyword)
        root->left = deleteKeyword(root->left, keyword);
    else if (keyword > root->keyword)
        root->right = deleteKeyword(root->right, keyword);
    else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;

            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            root->right = deleteKeyword(root->right, temp->keyword);
        }
    }

    if (root == nullptr)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to find the maximum number of comparisons required for finding any keyword
int maxComparisons(Node* root, string keyword) {
    int comparisons = 0;
    while (root != nullptr) {
        comparisons++;
        if (keyword < root->keyword)
            root = root->left;
        else if (keyword > root->keyword)
            root = root->right;
        else
            return comparisons;
    }
    return comparisons;
}

// Ascending order
void printInOrder(Node* root) {
    if (root != nullptr) {
        printInOrder(root->left);
        cout << root->keyword << " " << root->meaning << endl;
        printInOrder(root->right);
    }
}

// Descending order
void printReverseInOrder(Node* root) {
    if (root != nullptr) {
        printReverseInOrder(root->right);
        cout << root->keyword << " " << root->meaning << endl;
        printReverseInOrder(root->left);
    }
}

int main() {
    Node* root = nullptr;
    string keyword, meaning;

    while (true) {
        cout << "\n1. Add new keyword and meaning\n";
        cout << "2. Print all entries in ascending order\n";
        cout << "3. Print all entries in descending order\n";
        cout << "4. Delete a keyword from dictionary\n";
        cout << "5. Update the meaning of a keyword\n";
        cout << "6. Find maximum comparisons for a keyword\n";
        cout << "7. Exit program\n";
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
                    cout << "No entries to update." << endl;
                else {
                    cout << "Enter keyword to update: ";
                    cin >> keyword;
                    cout << "Enter new meaning: ";
                    cin >> meaning;
                    root = update(root, keyword, meaning);
                }
                break;
            case 6:
                if (root == nullptr)
                    cout << "No entries to search." << endl;
                else {
                    cout << "Enter keyword to search: ";
                    cin >> keyword;
                    int comparisons = maxComparisons(root, keyword);
                    cout << "Maximum comparisons required: " << comparisons << endl;
                }
                break;
            case 7:
                return 0;
            default:
                cout << "Invalid choice. Please choose a valid option." << endl;
        }
    }

    return 0;
}
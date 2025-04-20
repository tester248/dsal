#include <iostream>

using namespace std;

class BST
{
    struct Node
    {
        int data;
        Node *left, *right;

        Node(int val)
        {
            data = val;
            left = right = nullptr;
        }
    };
    Node *root;
public:
    BST()
    {
        root = nullptr;
    }

    Node *return_root() { return root; }

    void insert();
    void display(Node *);
    int search();
    int height(Node *);
    int findMin(Node *);
    void mirror(Node *);
    void mirrorTree();
};

void BST::insert()
{
    Node *temp = root;
    int val;
    cout << "\nEnter value of node: ";
    cin >> val;
    Node *newnode = new Node(val);

    if (root == NULL)
    {
        root = newnode;
        cout << "\nRoot node created"<<endl;
    }
    else
    {
        while (true)
        {
            if (val < temp->data)
            {
                if (temp->left == NULL)
                {
                    temp->left = newnode;
                    cout << "\nLeft node Inserted";
                    break;
                }
                else
                {
                    temp = temp->left;
                }
            }
            else if (val > temp->data)
            {
                if (temp->right == NULL)
                {
                    temp->right = newnode;
                    cout << "\nRight node inserted";
                    break;
                }
                else
                {
                    temp = temp->right;
                }
            }
            else
            {
                cout << "\nEntry repeated";
                break;
            }
        }
    }
}

void BST::display(Node *temp)
{
    if (temp != NULL)
    {
        display(temp->left);
        cout << "\t" << temp->data << " ";
        display(temp->right);
    }
}

int BST::search()
{
    Node *temp = root;
    int key;
    cout << "\nEnter the value to search: ";
    cin >> key;
    while (temp != NULL)
    {
        if (key < temp->data)
        {
            temp = temp->left;
        }
        else if (key > temp->data)
        {
            temp = temp->right;
        }
        else
        {
            cout << "\nValue " << key << " is present";
            return 1;
        }
    }
    return 0;
}

int BST::height(Node *node)
{
    if (node == NULL)
        return 0;
    else
    {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return max(leftHeight, rightHeight) + 1;
    }
}

int BST::findMin(Node *node)
{
    if (node == NULL)
    {
        cout << "\n\tTree is empty";
        return -1; 
    }
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node->data;
}

void BST::mirror(Node *node)
{
    if (node == NULL)
        return;

    Node *temp = node->left;
    node->left = node->right;
    node->right = temp;

    mirror(node->left);
    mirror(node->right);
}

void BST::mirrorTree()
{
    mirror(root);
}

int main()
{
    BST tree;
    int ch, i, val;
    do
    {
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

        switch (ch)
        {
        case 1:
            tree.insert();
            cout << "\n";
            break;
        case 2:
            cout << "\nTREE:\n";
            if (tree.return_root() == NULL)
                cout << "\nTree is empty";
            else
                tree.display(tree.return_root());
            cout << "\n";
            break;
        case 3:
            i = tree.search();
            if (i == 0)
            {
                cout << "\nValue is absent";
            }
            cout << "\n";
            break;
        case 4:
            cout << "\nHeight of the tree: " << tree.height(tree.return_root());
            cout << "\n";
            break;
        case 5:
            val = tree.findMin(tree.return_root());
            if (val != -1)
                cout << "\nMinimum value in the tree: " << val;
            cout << "\n";
            break;
        case 6:
            tree.mirrorTree();
            cout << "\nTree mirrored successfully";
            cout << "\n";
            break;
        case 7:
            break;
        default:
            cout << "\nINVALID INPUT";
            cout << "\n";
            break;
        }
    } while (ch < 7);
}

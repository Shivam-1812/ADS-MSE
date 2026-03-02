#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *left, *right;
    bool rThread;   // true if right pointer is thread
};

Node* root = NULL;

// Create new node
Node* createNode(int value)
{
    Node* temp = new Node;
    temp->data = value;
    temp->left = NULL;
    temp->right = NULL;
    temp->rThread = true;
    return temp;
}

// Insert into threaded binary tree
void insert(int value)
{
    Node *ptr = root;
    Node *parent = NULL;

    while(ptr != NULL)
    {
        if(value == ptr->data)
        {
            cout << "Duplicate value not allowed\n";
            return;
        }

        parent = ptr;

        if(value < ptr->data)
        {
            if(ptr->left == NULL)
                break;
            ptr = ptr->left;
        }
        else
        {
            if(ptr->rThread == false)
                ptr = ptr->right;
            else
                break;
        }
    }

    Node* newNode = createNode(value);

    if(parent == NULL)
        root = newNode;

    else if(value < parent->data)
    {
        parent->left = newNode;
        newNode->right = parent;
    }
    else
    {
        newNode->right = parent->right;
        parent->right = newNode;
        parent->rThread = false;
    }
}

// Find leftmost node
Node* leftMost(Node* temp)
{
    while(temp != NULL && temp->left != NULL)
        temp = temp->left;
    return temp;
}

// Inorder Traversal
void inorder()
{
    if(root == NULL)
    {
        cout << "Tree is empty\n";
        return;
    }

    Node* temp = leftMost(root);

    while(temp != NULL)
    {
        cout << temp->data << " ";

        if(temp->rThread)
            temp = temp->right;
        else
            temp = leftMost(temp->right);
    }
}

// Search element
void search(int key)
{
    Node* temp = root;

    while(temp != NULL)
    {
        if(key == temp->data)
        {
            cout << "Element found\n";
            return;
        }

        if(key < temp->data)
            temp = temp->left;
        else
        {
            if(temp->rThread)
                temp = NULL;
            else
                temp = temp->right;
        }
    }

    cout << "Element not found\n";
}

// Display tree (node with thread info)
void display(Node* temp)
{
    if(temp == NULL)
        return;

    display(temp->left);

    cout << "Node: " << temp->data;
    if(temp->rThread)
        cout << " (Thread to ";
    else
        cout << " (Right child ";

    if(temp->right != NULL)
        cout << temp->right->data << ")";
    else
        cout << "NULL)";

    cout << endl;

    if(temp->rThread == false)
        display(temp->right);
}

int main()
{
    int choice, value;

    do
    {
        cout << "\n1.Insert";
        cout << "\n2.Inorder Traversal";
        cout << "\n3.Search";
        cout << "\n4.Display";
        cout << "\n5.Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                insert(value);
                break;

            case 2:
                cout << "Inorder: ";
                inorder();
                cout << endl;
                break;

            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                search(value);
                break;

            case 4:
                display(root);
                break;

            case 5:
                cout << "Exit\n";
                break;

            default:
                cout << "Invalid choice\n";
        }

    } while(choice != 5);

    return 0;
}
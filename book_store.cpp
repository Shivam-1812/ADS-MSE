#include <iostream>
#include <string>
using namespace std;

struct Book
{
    string title;
    string author;
    float price;
    int stock;
    Book *left;
    Book *right;
};

Book* root = NULL;

// Create new book node
Book* createBook(string t, string a, float p, int s)
{
    Book* newBook = new Book;
    newBook->title = t;
    newBook->author = a;
    newBook->price = p;
    newBook->stock = s;
    newBook->left = NULL;
    newBook->right = NULL;
    return newBook;
}

// Insert book into BST (based on title)
Book* insertBook(Book* root, string t, string a, float p, int s)
{
    if(root == NULL)
        return createBook(t, a, p, s);

    if(t < root->title)
        root->left = insertBook(root->left, t, a, p, s);
    else if(t > root->title)
        root->right = insertBook(root->right, t, a, p, s);

    return root;
}

// Search book by title
Book* searchByTitle(Book* root, string key)
{
    if(root == NULL || root->title == key)
        return root;

    if(key < root->title)
        return searchByTitle(root->left, key);
    else
        return searchByTitle(root->right, key);
}

// Search books by author (traversal required)
void searchByAuthor(Book* root, string author)
{
    if(root == NULL)
        return;

    searchByAuthor(root->left, author);

    if(root->author == author)
    {
        cout << "\nTitle: " << root->title;
        cout << "\nPrice: " << root->price;
        cout << "\nStock: " << root->stock << endl;
    }

    searchByAuthor(root->right, author);
}

// Update book information
void updateBook(Book* root, string key)
{
    Book* temp = searchByTitle(root, key);

    if(temp == NULL)
    {
        cout << "\nBook not found!\n";
        return;
    }

    cout << "\nEnter new price: ";
    cin >> temp->price;

    cout << "Enter new stock: ";
    cin >> temp->stock;

    cout << "Book updated successfully!\n";
}

// Display books (Inorder traversal)
void displayBooks(Book* root)
{
    if(root == NULL)
        return;

    displayBooks(root->left);

    cout << "\nTitle: " << root->title;
    cout << "\nAuthor: " << root->author;
    cout << "\nPrice: " << root->price;
    cout << "\nStock: " << root->stock << endl;

    displayBooks(root->right);
}

int main()
{
    int choice;
    string title, author;
    float price;
    int stock;

    do
    {
        cout << "\n1. Add Book";
        cout << "\n2. Search by Title";
        cout << "\n3. Search by Author";
        cout << "\n4. Update Book";
        cout << "\n5. Display All Books";
        cout << "\n6. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice)
        {
            case 1:
                cout << "Enter title: ";
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                cout << "Enter price: ";
                cin >> price;
                cout << "Enter stock: ";
                cin >> stock;
                root = insertBook(root, title, author, price, stock);
                break;

            case 2:
                cout << "Enter title to search: ";
                getline(cin, title);
                {
                    Book* result = searchByTitle(root, title);
                    if(result != NULL)
                    {
                        cout << "\nBook Found!";
                        cout << "\nAuthor: " << result->author;
                        cout << "\nPrice: " << result->price;
                        cout << "\nStock: " << result->stock << endl;
                    }
                    else
                        cout << "\nBook not found!\n";
                }
                break;

            case 3:
                cout << "Enter author name: ";
                getline(cin, author);
                searchByAuthor(root, author);
                break;

            case 4:
                cout << "Enter title to update: ";
                getline(cin, title);
                updateBook(root, title);
                break;

            case 5:
                displayBooks(root);
                break;

            case 6:
                cout << "Exiting...";
                break;

            default:
                cout << "Invalid choice!";
        }

    } while(choice != 6);

    return 0;
}
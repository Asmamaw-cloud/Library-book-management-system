#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Book {
    string bookNumber;
    string title;
    string author;
    string publicationYear;
    string edition;
    Book* left, * right;
};

Book* rootNodePtr = NULL;
// The function validate book title and author
bool isValidString(const string& str) {
    for (char ch : str) {
        if (!isalpha(ch) && ch != ' ') {
            return false;
        }
    }
    return true;
}
// The function validate books' publication year
bool validateYear(const string& year) {
    int intYear = stoi(year);
    if (year.empty() || !isdigit(year[0]) ||intYear > 2024) {
        return false;
    }
     return true;
}
// The function validate book number
bool isInteger(const string& str) {
    if (str.empty() || (!isdigit(str[0]) && str[0] != '+' && str[0] != '-')) {
        return false;
    }
    for (size_t i = 1; i < str.length(); ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

void writeBooksToFileHelper(Book* node, ofstream& file) {
    if (node == NULL){
        cout<<"Empty book!"<<endl;
        return;
        }
    file << node->bookNumber << endl;
    file << node->title << endl;
    file << node->author << endl;
    file << node->publicationYear << endl;
    writeBooksToFileHelper(node->left, file);
    writeBooksToFileHelper(node->right, file);
}

void writeBooksToFile(const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Error: Failed to open file " << filename << " for writing." << endl;
        return;
    }
    writeBooksToFileHelper(rootNodePtr, file);
    file.close();
    cout << "Books written to file successfully!" << endl;
}

void InsertBook(const string& Number, const string& Title, const string& Author, const string& pubYear) {
    Book* newNode = new Book;
    newNode->bookNumber = Number;
    newNode->title = Title;
    newNode->author = Author;
    newNode->publicationYear = pubYear;
    newNode->left = NULL;
    newNode->right = NULL;

    if (rootNodePtr == NULL) {
        rootNodePtr = newNode;
        cout<<"The book is inserted to the file succrssfull!"<<endl;
        return;
    }

    Book* currentNode = rootNodePtr;
    while (true) {
        if (Number < currentNode->bookNumber) {
            if (currentNode->left == NULL) {
                currentNode->left = newNode;
                cout<<"The book is inserted to the file succrssfull!"<<endl;
                return;
            }
            currentNode = currentNode->left;
        } else if (Number > currentNode->bookNumber) {
            if (currentNode->right == NULL) {
                currentNode->right = newNode;
                cout<<"The book is inserted to the file succrssfull!"<<endl;
                return;
            }
            currentNode = currentNode->right;
        } else {
            cout << "Error: Book with Book Number " << Number << " already exists. Please use another unassigned Book Number." << endl;
            delete newNode; // Avoid memory leak
            return;
        }
    }
}

// void Display(Book* node) {
//     if (node != NULL) {
//         Display(node->left);
//         cout << "  " << node->bookNumber << "\t\t" << node->title << "\t\t" << node->author << "\t\t" << node->publicationYear << "\t" << endl;
//         Display(node->right);
//     }
// }

void readBooksFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Failed to open file " << filename << "." << endl;
        return;
    }

    string bookNumber, title, author, publicationYear;

    while (file >> bookNumber) {
        file.ignore(); // Ignore whitespace
        getline(file, title);
        getline(file, author);
        getline(file, publicationYear);

        InsertBook(bookNumber, title, author, publicationYear);
    }

    file.close();
}

void displayBook(Book* node)
{
    cout<<"\n________________________________________________________________"<<endl;
        cout << "|  " << "book_Number" << "\t\t"<< node->bookNumber <<endl;
        cout << "|  " << "title" << "\t\t"<<node->title <<endl;
        cout << "|  " << "author" << "\t\t"<< node->author <<endl;
        cout << "| "  "publicationYear" << "\t"<< node->publicationYear<< endl;
        cout<<"|________________________________________________________________"<<endl;
}

void SearchBookByAttributeHelper(Book* node, const string& attribute) {
    if (node == NULL)
        return;

    if (node->bookNumber == attribute || node->title == attribute || node->author == attribute || node->publicationYear == attribute){
        displayBook(node);
        }
    SearchBookByAttributeHelper(node->left, attribute);
    SearchBookByAttributeHelper(node->right, attribute);
}

void SearchByBookNumber() {
    string number;
    cout << "Enter the book number you want to search?" << endl;
    cin >> number;
    if (!isInteger(number)) {
        cout << "Not a valid integer input." << endl;
        return;
    }
    if (rootNodePtr == NULL) {
        cout << "Library is empty!" << endl;
        return;
    }
    SearchBookByAttributeHelper(rootNodePtr, number);
}

void SearchByBookTitle() {
    string title;
    cout << "Enter the book title you want to search?" << endl;
    cin.ignore(); // Ignore newline character from previous input
    getline(cin, title); // Changed to getline to allow spaces in title
    if (!isValidString(title)) {
        cout << "Please enter a valid book title!" << endl;
        return;
    }
    if (rootNodePtr == NULL) {
        cout << "Library is empty!" << endl;
        return;
    }
    SearchBookByAttributeHelper(rootNodePtr, title);
}

void SearchByBookAuthor() {
    string author;
    cout << "Enter the book author you want to search?" << endl;
    cin.ignore(); // Ignore newline character from previous input
    getline(cin, author); // Changed to getline to allow spaces in author
    if (!isValidString(author)) {
        cout << "Please enter a valid author name!" << endl;
        return;
    }
    if (rootNodePtr == NULL) {
        cout << "Library is empty!" << endl;
        return;
    }
    SearchBookByAttributeHelper(rootNodePtr, author);
}

void SearchByPubYear() {
    string year;
    year:
    cout << "Enter the publication year you want to search?" << endl;
    cin.ignore(); // Ignore newline character from previous input
    getline(cin, year); // Changed to getline to allow spaces in year
    if(!validateYear(year)){
                    cout<<"Please enter the valid year!"<<endl;
                    goto year;
                }
    if (rootNodePtr == NULL) {
        cout << "Library is empty!" << endl;
        return;
    }
    SearchBookByAttributeHelper(rootNodePtr, year);
}

void SearchBook() {
    char ch;
    do {
        int choice;
        cout << "1. Search by book number" << endl;
        cout << "2. Search by book title" << endl;
        cout << "3. Search by book author" << endl;
        cout << "4. Search by publication year" << endl;
        cout << "5. Back to the main menu" << endl;
        cin >> choice;
        switch (choice) {
        case 1:
            system("cls");
            SearchByBookNumber();
            break;
        case 2:
            system("cls");
            SearchByBookTitle();
            break;
        case 3:
            system("cls");
            SearchByBookAuthor();
            break;
        case 4:
            system("cls");
            SearchByPubYear();
            break;
        case 5:
            return; // Exit the function
        default:
            cout << "Please insert the correct number!" << endl;
        }
        cout << "Press y to continue!" << endl;
        cin >> ch;
        system("cls");
    } while (ch == 'Y' || ch == 'y');
}

void MaxBook() {
    if (rootNodePtr == NULL) {
        cout << "Library is empty!" << endl;
        return;
    }
    Book* currentNode = rootNodePtr;
    while (currentNode->right != NULL)
        currentNode = currentNode->right;

    cout << "Maximum Book:" << endl;
    displayBook(currentNode);
}

void MinBook() {
    if (rootNodePtr == NULL) {
        cout << "Library is empty!" << endl;
        return;
    }

    Book* currentNode = rootNodePtr;
    while (currentNode->left != NULL)
        currentNode = currentNode->left;

    cout << "Minimum Book:" << endl;
    displayBook(currentNode);
    // Display(currentNode);
    // cout << "  " << currentNode->bookNumber << "\t\t" << currentNode->title << "\t\t" << currentNode->author << "\t\t" << currentNode->publicationYear << "\t" << endl;
}

void displayBooksPreorderHelper(Book* node) {
    if (node == NULL)
        return;
        
    cout << "  " << node->bookNumber << "\t\t" << node->title << "\t\t" << node->author << "\t\t" << node->publicationYear << "\t" << endl;
    // Display(node);
    displayBooksPreorderHelper(node->left);
    displayBooksPreorderHelper(node->right);
}

void DisplayPreorder() {
    if (rootNodePtr == NULL) {
        cout << "Library is empty!" << endl;
        return;
    }

    cout << "Books in Preorder format:" << endl;
    cout<<"  Book_number\t\t"<<"Book_title\t\t"<<"Author"<<"Publication_year"<<endl;
    displayBooksPreorderHelper(rootNodePtr);
}

void displayBooksInorderHelper(Book* node) {
    if (node == NULL)
        return;

    displayBooksInorderHelper(node->left);
    cout << "  " << node->bookNumber << "\t\t" << node->title << "\t\t" << node->author << "\t\t" << node->publicationYear << "\t" << endl;
    displayBooksInorderHelper(node->right);
}

void DisplayInorder() {
    if (rootNodePtr == NULL) {
        cout << "Library is empty!" << endl;
        return;
    }

    cout << "Books in Inorder format:" << endl;
    cout<<"  Book_number\t\t"<<"Book_title\t\t"<<"Author"<<"Publication_year"<<endl;
    displayBooksInorderHelper(rootNodePtr);
}

void displayBooksPostorderHelper(Book* node) {
    if (node == NULL)
        return;

    displayBooksPostorderHelper(node->left);
    displayBooksPostorderHelper(node->right);
    cout << "  " << node->bookNumber << "\t\t\t" << node->title << "\t\t" << node->author << "\t\t" << node->publicationYear << "\t" << endl;
}

void DisplayPostorder() {
    if (rootNodePtr == NULL) {
        cout << "Library is empty!" << endl;
        return;
    }

    cout << "Books in Postorder format:" << endl;
    cout<<"  Book_number\t\t"<<"Book_title\t\t"<<"Author\t\t"<<"Publication_year"<<endl;
    displayBooksPostorderHelper(rootNodePtr);
}

void DisplayBooks() {
    char ch;
    do {
        int choice;
        cout << "1. Display maximum book number" << endl;
        cout << "2. Display minimum book number" << endl;
        cout << "3. Display in preorder" << endl;
        cout << "4. Display in inorder" << endl;
        cout << "5. Display in postorder" << endl;
        cout << "6. Back to main menu" << endl;
        cin >> choice;
        switch (choice) {
        case 1:
            system("cls");
            MaxBook();
            break;
        case 2:
            system("cls");
            MinBook();
            break;
        case 3:
            system("cls");
            DisplayPreorder();
            break;
        case 4:
            system("cls");
            DisplayInorder();
            break;
        case 5:
            system("cls");
            DisplayPostorder();
            break;
        case 6:
            system("cls");
            system("cls");
            return;
        default:
            cout << "Please insert the correct number!" << endl;
        }
        cout << "press y to continue!" << endl;
        cin >> ch;
        system("cls");
    } while (ch == 'Y' || ch == 'y');
}

// Function to count the total number of books
int CountBooks(Book* node) {
    if (node == NULL)
        return 0;

    return 1 + CountBooks(node->left) + CountBooks(node->right);
}

void singleLeftRotation(Book*& node) {
    if (node == NULL || node->right == NULL){
    cout<<"you can't perform left rotation."<<endl;
        return;
    }
    Book* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    node = newRoot;
    rootNodePtr = node;
    cout << "Single left rotation is applied successfully!" << endl;
}

void singleRightRotation(Book*& node) {
    if (node == NULL || node->left == NULL){
    cout<<"you can't perform right rotation."<<endl;
        return;
    }
    Book* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    node = newRoot;
    rootNodePtr = node;
    cout << "Single right rotation is applied successfully!" << endl;
}

void doubleLeftRotation(Book*& node) {
    if (node == NULL || node->right == NULL || node->right->left == NULL){
        cout<<"you can't perform left rotation."<<endl;
        return;
    }
    node->right = node->right->right;
    singleLeftRotation(node);
    cout << "Double left rotation is applied successfully!" << endl;
}

void doubleRightRotation(Book*& node) {
    if (node == NULL || node->left == NULL || node->left->right == NULL){
        cout<<"you can't perform right rotation."<<endl;
        return;
    }
    node->left = node->left->left;
    singleRightRotation(node);
    cout << "Double right rotation is applied successfully!" << endl;
}

void Rotation() {
    char ch;
    if (rootNodePtr == NULL) {
        cout << "Library is empty!" << endl;
        return;
    }
    do {
        int choice;
        cout << "1. Single Left Rotation" << endl;
        cout << "2. Single Right Rotation" << endl;
        cout << "3. Double Left Rotation" << endl;
        cout << "4. Double Right Rotation" << endl;
        cout << "5. Go to main menu" << endl;
        cin >> choice;
        switch (choice) {
            case 1:
                singleLeftRotation(rootNodePtr);
                break;
            case 2:
                singleRightRotation(rootNodePtr);
                break;
            case 3:
                doubleLeftRotation(rootNodePtr);
                break;
            case 4:
                doubleRightRotation(rootNodePtr);
                break;
            case 5:
                return;
            default:
                cout << "Please insert the correct number!" << endl;
        }
        cout << "Do you want to continue?" << endl;
        cin >> ch;
    } while (ch == 'Y' || ch == 'y');
    system("cls");
    cout << "Rotations performed successfully!" << endl;
}

void DeleteMaxBook() {
    if (rootNodePtr == NULL) {
        cout << "Library is empty!" << endl;
        return;
    }

    if (rootNodePtr->right == NULL) {
        Book* temp = rootNodePtr;
        rootNodePtr = rootNodePtr->left;
        delete temp;
        cout << "Book deleted successfully!" << endl;
        return;
    }

    Book* parent = rootNodePtr;
    Book* currentNode = rootNodePtr->right;
    while (currentNode->right != NULL) {
        parent = currentNode;
        currentNode = currentNode->right;
    }

    parent->right = currentNode->left;
    delete currentNode;
    cout << "Book deleted successfully!" << endl;
}

void DeleteMinBook() {
    if (rootNodePtr == NULL) {
        cout << "Library is empty!" << endl;
        return;
    }

    if (rootNodePtr->left == NULL) {
        Book* temp = rootNodePtr;
        rootNodePtr = rootNodePtr->right;
        delete temp;
        cout << "Book deleted successfully!" << endl;
        return;
    }

    Book* parent = rootNodePtr;
    Book* currentNode = rootNodePtr->left;
    while (currentNode->left != NULL) {
        parent = currentNode;
        currentNode = currentNode->left;
    }

    parent->left = currentNode->right;
    delete currentNode;
    cout << "Book deleted successfully!" << endl;
}

void DeleteNode(Book* parent, Book* node, bool isLeftChild) {
    if (node->left == NULL && node->right == NULL) {
        if (isLeftChild)
            parent->left = NULL;
        else
            parent->right = NULL;
        delete node;
    } else if (node->left == NULL) {
        if (isLeftChild)
            parent->left = node->right;
        else
            parent->right = node->right;
        delete node;
    } else if (node->right == NULL) {
        if (isLeftChild)
            parent->left = node->left;
        else
            parent->right = node->left;
        delete node;
    } else {
        Book* parentSuccessor = node;
        Book* successor = node->right;

        while (successor->left != NULL) {
            parentSuccessor = successor;
            successor = successor->left;
        }

        if (parentSuccessor != node) {
            parentSuccessor->left = successor->right;
        } else {
            node->right = successor->right;
        }

        node->bookNumber = successor->bookNumber;
        node->title = successor->title;
        node->author = successor->author;
        node->publicationYear = successor->publicationYear;
        delete successor;
    }
}

void DeleteRoot() {
    if (rootNodePtr->left == NULL && rootNodePtr->right == NULL) {
        delete rootNodePtr;
        rootNodePtr = NULL;
        cout<<"Now the tree is empty"<<endl;
    } else if (rootNodePtr->left == NULL) {
        Book* temp = rootNodePtr;
        rootNodePtr = rootNodePtr->right;
        delete temp;
    } else if (rootNodePtr->right == NULL) {
        Book* temp = rootNodePtr;
        rootNodePtr = rootNodePtr->left;
        delete temp;
    } else {
        Book* parent = NULL;
        Book* currentNode = rootNodePtr->right;

        while (currentNode->left != NULL) {
            parent = currentNode;
            currentNode = currentNode->left;
        }

        if (parent != NULL) {
            parent->left = currentNode->right;
        } else {
            rootNodePtr->right = currentNode->right;
        }

        rootNodePtr->bookNumber = currentNode->bookNumber;
        rootNodePtr->title = currentNode->title;
        rootNodePtr->author = currentNode->author;
        rootNodePtr->publicationYear = currentNode->publicationYear;
        delete currentNode;
    }
}

void DeleteYourBook() {
    string bookNumber;
    In:
    cout << "Enter the book number you want to delete: ";
    cin >> bookNumber;
    if (!isInteger(bookNumber)) {
        cout << "Not a valid integer input." << endl;
        goto In;
    }
    if (rootNodePtr == NULL) {
        cout << "Library is empty!" << endl;
        return;
    }

    Book* parent = NULL;
    Book* currentNode = rootNodePtr;

    while (currentNode != NULL && currentNode->bookNumber != bookNumber) {
        parent = currentNode;
        if (bookNumber < currentNode->bookNumber)
            currentNode = currentNode->left;
        else
            currentNode = currentNode->right;
    }

    if (currentNode == NULL) {
        cout << "Book with Book Number " << bookNumber << " not found!" << endl;
        return;
    }

    if (currentNode == rootNodePtr)
        DeleteRoot();
    else if (currentNode == parent->left)
        DeleteNode(parent, currentNode, true);
    else
        DeleteNode(parent, currentNode, false);

    cout << "Book deleted successfully!" << endl;
}

void DeleteBook() {
    char ch;
    do {
        int choice;
        cout << "1. Delete maximum book number" << endl;
        cout << "2. Delete minimum book number" << endl;
        cout << "3. Delete the root" << endl;
        cout << "4. Delete your book" << endl;
        cout << "5. Go to main menu" << endl;

        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                DeleteMaxBook();
                break;
            case 2:
                DeleteMinBook();
                break;
            case 3:
                DeleteRoot();
                break;
            case 4:
                DeleteYourBook();
                break;
            case 5:
                return;
            default:
                cout << "Please insert the correct number!" << endl;
        }
        cout << "Do you want to continue?" << endl;
        cin >> ch;
        system("cls");
    } while (ch == 'Y' || ch == 'y');
}

int main() {
    int ch;
    string filename;
    do {
        // system("cls");
        cout << "\n\t\tWelcome to Library Management System\n" << endl;
        main:
        cout << "\t\t\t1. Insert Book Record" << endl;
        cout << "\t\t\t2. Display Book Record" << endl;
        cout << "\t\t\t3. Search Book" << endl;
        cout << "\t\t\t4. Count the number of books" << endl;
        cout << "\t\t\t5. Rotation" << endl;
        cout << "\t\t\t6. Delete Book Record" << endl;
        cout << "\t\t\t7. Write books to file" << endl;
        cout << "\t\t\t8. Read books from file" << endl;
        cout << "\t\t\t9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        switch (ch) {
            case 1: {
                // system("cls");
                again:
                string Number, Title, Author, pubYear;
                In:
                cout << "Enter the book number: ";
                cin >> Number;
                if (!isInteger(Number)) {
                    cout << "please enter the valid book number!" << endl;
                    goto In;
                    }
                title:
                cout << "Enter the book title: ";
                cin.ignore(); // Ignore newline character from previous input
                getline(cin, Title);
                if(!isValidString(Title))
                {
                    cout<<"Please enter the valid book title!"<<endl;
                    goto title;
                }
                author:
                cout << "Enter the book author: ";
                getline(cin, Author);
                if(!isValidString(Author))
                {
                    cout<<"Please enter the valid author name!"<<endl;
                    goto author;
                }
                year:
                cout << "Enter the publication year: ";
                cin >> pubYear;
                if (!validateYear(pubYear)) {
                    cout << "Invalid publication year! Publication year must be between 0 and 2024." << endl;
                    goto year;
                }
                InsertBook(Number, Title, Author, pubYear);
                char c;
                system("cls");
                cout<<"press y to add more books"<<endl;
                cin>>c;
                if(c =='Y'|| c == 'y')
                goto again;
                break;
            }
            case 2:
                system("cls");
                DisplayBooks();
                break;
            case 3:
                system("cls");
                SearchBook();
                break;
            case 4:
                {
                int total = CountBooks(rootNodePtr);
                system("cls");
                cout << "The total number of books in the library is: " << total << endl;
                char c;
                cout<<"press y to go to the MAIN menu"<<endl;
                cin>>c;
                if(c=='y'||c=='Y')
                goto main;
                exit(0);
            }
            case 5:
                system("cls");
                Rotation();
                break;
            case 6:
                system("cls");
                DeleteBook();
                break;
            case 7:
                system("cls");
                cout << "Enter the filename to write books to: ";
                cin >> filename;
                writeBooksToFile(filename);
                break;
            case 8:
                system("cls");
                cout << "Enter the filename to read books from: ";
                cin >> filename;
                readBooksFromFile(filename);
                break;
            case 9:
                cout << "Thank you for using the Library Management System!" << endl;
                break;
            default:
                system("cls");
                cout << "Please insert the correct number!" << endl;
                goto main;
        }
    } while (ch != 9);
    return 0;
}

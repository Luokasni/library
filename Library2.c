
#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 50
#define MAX_USERS 10

// Department definitions
#define MATHS 1
#define PHYSICS 2
#define CHEMISTRY 3

typedef struct {
    int id;
    char title[100];
    int department;
    char borrowed_by[30];
} Book;

typedef struct {
    char username[30];
    char password[30];
    int department;
} Student;

// Initial book collection
Book books[MAX_BOOKS] = {
    {1, "Algebra", MATHS, ""},
    {2, "Calculus", MATHS, ""},
    {3, "Statistics", MATHS, ""},
    {4, "Mechanics", PHYSICS, ""},
    {5, "Optics", PHYSICS, ""},
    {6, "Thermodynamics", PHYSICS, ""},
    {7, "Organic Chemistry", CHEMISTRY, ""},
    {8, "Inorganic Chemistry", CHEMISTRY, ""},
    {9, "Biochemistry", CHEMISTRY, ""}
};

int bookCount = 9;

// Student login credentials
Student students[MAX_USERS] = {
    {"M101", "math123", MATHS},
    {"P101", "phy123", PHYSICS},
    {"C101", "chem123", CHEMISTRY}
};

int studentCount = 3;

// Get department name
char *getDepartmentName(int department) {
    switch (department) {
        case MATHS: return "Mathematics";
        case PHYSICS: return "Physics";
        case CHEMISTRY: return "Chemistry";
        default: return "Unknown";
    }
}

// Display books
void displayBooks(int department) {
    int i, found = 0;

    printf("\n--- BOOK LIST ---\n");

    for (i = 0; i < bookCount; i++) {

        if (department == 0 ||
            books[i].department == department) {

            printf("\nID: %d", books[i].id);
            printf("\nTitle: %s", books[i].title);
            printf("\nDepartment: %s",
                   getDepartmentName(books[i].department));

            if (strcmp(books[i].borrowed_by, "") == 0)
                printf("\nStatus: Available\n");
            else
                printf("\nStatus: Borrowed\n");

            found = 1;
        }
    }

    if (!found)
        printf("No books available.\n");
}

// Search books
void searchBook(int department) {
    char search[100];
    int i, found = 0;

    printf("\nEnter book title to search: ");
    scanf(" %99[^\n]", search);

    for (i = 0; i < bookCount; i++) {

        if ((department == 0 ||
             books[i].department == department) &&
            strstr(books[i].title, search) != NULL) {

            printf("\nBook ID: %d", books[i].id);
            printf("\nTitle: %s", books[i].title);
            printf("\nDepartment: %s",
                   getDepartmentName(books[i].department));

            printf("\nStatus: %s\n",
                strcmp(books[i].borrowed_by, "") == 0
                ? "Available" : "Borrowed");

            found = 1;
        }
    }

    if (!found)
        printf("\nBook not found or access denied.\n");
}

// Borrow a book
void borrowBook(int department, char username[]) {
    int id, i;

    printf("\nEnter Book ID to borrow: ");
    scanf("%d", &id);

    for (i = 0; i < bookCount; i++) {

        if (books[i].id == id) {

            if (books[i].department != department) {
                printf("\nAccess Denied! "
                       "You cannot borrow books "
                       "from another department.\n");
                return;
            }

            if (strcmp(books[i].borrowed_by, "") != 0) {
                printf("\nBook is already borrowed.\n");
                return;
            }

            strcpy(books[i].borrowed_by, username);

            printf("\nBook borrowed successfully!\n");
            return;
        }
    }

    printf("\nInvalid Book ID.\n");
}

// Return a book
void returnBook(char username[]) {
    int id, i;

    printf("\nEnter Book ID to return: ");
    scanf("%d", &id);

    for (i = 0; i < bookCount; i++) {

        if (books[i].id == id) {

            if (strcmp(books[i].borrowed_by, username) == 0) {

                strcpy(books[i].borrowed_by, "");

                printf("\nBook returned successfully!\n");
                return;
            }
            else {
                printf("\nYou have not borrowed this book.\n");
                return;
            }
        }
    }

    printf("\nInvalid Book ID.\n");
}

// Add a new book (Admin only)
void addBook() {
    int department;

    if (bookCount >= MAX_BOOKS) {
        printf("\nLibrary book storage is full.\n");
        return;
    }

    books[bookCount].id = bookCount + 1;

    printf("\nEnter book title: ");
    scanf(" %99[^\n]", books[bookCount].title);

    printf("\nSelect department:\n");
    printf("1. Mathematics\n");
    printf("2. Physics\n");
    printf("3. Chemistry\n");

    printf("Enter choice: ");
    scanf("%d", &department);

    if (department < 1 || department > 3) {
        printf("\nInvalid department.\n");
        return;
    }

    books[bookCount].department = department;
    strcpy(books[bookCount].borrowed_by, "");

    bookCount++;

    printf("\nBook added successfully!\n");
}

// Student menu
void studentMenu(int department, char username[]) {
    int choice;

    do {
        printf("\n===== STUDENT MENU =====\n");
        printf("Department: %s\n",
               getDepartmentName(department));

        printf("1. View Department Books\n");
        printf("2. Search Book\n");
        printf("3. Borrow Book\n");
        printf("4. Return Book\n");
        printf("5. Logout\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayBooks(department);
                break;

            case 2:
                searchBook(department);
                break;

            case 3:
                borrowBook(department, username);
                break;

            case 4:
                returnBook(username);
                break;

            case 5:
                printf("\nStudent logged out.\n");
                break;

            default:
                printf("\nInvalid choice.\n");
        }

    } while (choice != 5);
}

// Admin menu
void adminMenu() {
    int choice;

    do {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. View All Books\n");
        printf("2. Search All Books\n");
        printf("3. Add New Book\n");
        printf("4. Logout\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayBooks(0);
                break;

            case 2:
                searchBook(0);
                break;

            case 3:
                addBook();
                break;

            case 4:
                printf("\nAdmin logged out.\n");
                break;

            default:
                printf("\nInvalid choice.\n");
        }

    } while (choice != 4);
}

// Login function
void login() {
    char username[30], password[30];
    int i;

    printf("\nEnter Username: ");
    scanf("%29s", username);

    printf("Enter Password: ");
    scanf("%29s", password);

    // Admin authentication
    if (strcmp(username, "admin") == 0 &&
        strcmp(password, "admin123") == 0) {

        printf("\nAdmin Login Successful!\n");
        adminMenu();
        return;
    }

    // Student authentication
    for (i = 0; i < studentCount; i++) {

        if (strcmp(username, students[i].username) == 0 &&
            strcmp(password, students[i].password) == 0) {

            printf("\nStudent Login Successful!\n");

            studentMenu(students[i].department,
                        students[i].username);
            return;
        }
    }

    printf("\nInvalid Username or Password!\n");
}

// Main function
int main() {
    int choice;

    printf("=================================\n");
    printf("   COLLEGE LIBRARY MANAGEMENT\n");
    printf("=================================\n");

    do {
        printf("\n1. Login\n");
        printf("2. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login();
                break;

            case 2:
                printf("\nThank you for using the library!\n");
                break;

            default:
                printf("\nInvalid choice.\n");
        }

    } while (choice != 2);

    return 0;
}

    

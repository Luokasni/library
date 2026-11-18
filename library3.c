
#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 50

#define MATHS 1
#define PHYSICS 2
#define CHEMISTRY 3

typedef struct {
    int id;
    char title[100];
    int department;
    char borrowedBy[30];
} Book;

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

// Get department name
char *getDepartmentName(int department)
{
    switch (department) {
        case MATHS:
            return "Mathematics";

        case PHYSICS:
            return "Physics";

        case CHEMISTRY:
            return "Chemistry";

        default:
            return "Unknown";
    }
}

// Check department access
int hasAccess(int studentDepartment, int bookDepartment)
{
    return studentDepartment == bookDepartment;
}

// Select student department
int selectDepartment()
{
    int choice;

    printf("\nSelect Department:\n");
    printf("1. Mathematics\n");
    printf("2. Physics\n");
    printf("3. Chemistry\n");

    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > 3) {
        printf("\nInvalid department!\n");
        return 0;
    }

    return choice;
}

// Display books
void displayBooks(int department)
{
    int i, found = 0;

    printf("\n===== BOOK LIST =====\n");

    for (i = 0; i < bookCount; i++) {

        // Admin (0) can access all books
        // Students can access only their department

        if (department == 0 ||
            hasAccess(department, books[i].department)) {

            printf("\nBook ID: %d\n", books[i].id);
            printf("Title: %s\n", books[i].title);
            printf("Department: %s\n",
                   getDepartmentName(books[i].department));

            if (strcmp(books[i].borrowedBy, "") == 0)
                printf("Status: Available\n");
            else
                printf("Status: Borrowed\n");

            found = 1;
        }
    }

    if (!found)
        printf("\nNo books available.\n");
}

// Search books
void searchBook(int department)
{
    char search[100];
    int i, found = 0;

    printf("\nEnter book title: ");
    scanf(" %99[^\n]", search);

    for (i = 0; i < bookCount; i++) {

        if ((department == 0 ||
             hasAccess(department, books[i].department)) &&
            strstr(books[i].title, search) != NULL) {

            printf("\nBook ID: %d\n", books[i].id);
            printf("Title: %s\n", books[i].title);
            printf("Department: %s\n",
                   getDepartmentName(books[i].department));

            printf("Status: %s\n",
                strcmp(books[i].borrowedBy, "") == 0
                ? "Available" : "Borrowed");

            found = 1;
        }
    }

    if (!found)
        printf("\nBook not found or access denied.\n");
}

// Borrow book
void borrowBook(int department, char studentID[])
{
    int id, i;

    printf("\nEnter Book ID to borrow: ");
    scanf("%d", &id);

    for (i = 0; i < bookCount; i++) {

        if (books[i].id == id) {

            if (!hasAccess(department, books[i].department)) {
                printf("\nACCESS DENIED!\n");
                printf("You cannot borrow books "
                       "from another department.\n");
                return;
            }

            if (strcmp(books[i].borrowedBy, "") != 0) {
                printf("\nBook is already borrowed.\n");
                return;
            }

            strcpy(books[i].borrowedBy, studentID);

            printf("\nBook borrowed successfully!\n");
            return;
        }
    }

    printf("\nInvalid Book ID.\n");
}

// Return book
void returnBook(char studentID[])
{
    int id, i;

    printf("\nEnter Book ID to return: ");
    scanf("%d", &id);

    for (i = 0; i < bookCount; i++) {

        if (books[i].id == id) {

            if (strcmp(books[i].borrowedBy, studentID) == 0) {

                strcpy(books[i].borrowedBy, "");

                printf("\nBook returned successfully!\n");
                return;
            }

            printf("\nYou have not borrowed this book.\n");
            return;
        }
    }

    printf("\nInvalid Book ID.\n");
}

// Admin adds books
void addBook()
{
    int department;

    if (bookCount >= MAX_BOOKS) {
        printf("\nBook storage is full!\n");
        return;
    }

    printf("\nEnter Book Title: ");
    scanf(" %99[^\n]", books[bookCount].title);

    printf("\n");
    department = selectDepartment();

    if (department == 0)
        return;

    books[bookCount].id = books[bookCount - 1].id + 1;
    books[bookCount].department = department;

    strcpy(books[bookCount].borrowedBy, "");

    bookCount++;

    printf("\nBook added successfully!\n");
}

// Student menu
void studentMenu(int department, char name[], char studentID[])
{
    int choice;

    do {
        printf("\n===== STUDENT MENU =====\n");
        printf("Welcome, %s\n", name);
        printf("Student ID: %s\n", studentID);
        printf("Department: %s\n",
               getDepartmentName(department));

        printf("\n1. View Department Books\n");
        printf("2. Search Book\n");
        printf("3. Borrow Book\n");
        printf("4. Return Book\n");
        printf("5. Logout\n");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                displayBooks(department);
                break;

            case 2:
                searchBook(department);
                break;

            case 3:
                borrowBook(department, studentID);
                break;

            case 4:
                returnBook(studentID);
                break;

            case 5:
                printf("\nStudent logged out.\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while (choice != 5);
}

// Admin menu
void adminMenu()
{
    int choice;

    do {
        printf("\n===== ADMIN MENU =====\n");

        printf("1. View All Books\n");
        printf("2. Search All Books\n");
        printf("3. Add New Book\n");
        printf("4. Logout\n");

        printf("\nEnter choice: ");
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
                printf("\nInvalid choice!\n");
        }

    } while (choice != 4);
}

// Admin login
void adminLogin()
{
    char username[30];
    char password[30];

    printf("\nEnter Admin Username: ");
    scanf("%29s", username);

    printf("Enter Admin Password: ");
    scanf("%29s", password);

    if (strcmp(username, "admin") == 0 &&
        strcmp(password, "admin123") == 0) {

        printf("\nAdmin Login Successful!\n");
        adminMenu();
    }
    else {
        printf("\nInvalid Admin Credentials!\n");
    }
}

// Student login
void studentLogin()
{
    char name[50];
    char studentID[30];
    int department;

    printf("\nEnter Student Name: ");
    scanf(" %49[^\n]", name);

    printf("Enter Student ID: ");
    scanf("%29s", studentID);

    department = selectDepartment();

    if (department == 0) {
        printf("\nStudent Login Failed!\n");
        return;
    }

    printf("\nStudent Login Successful!\n");

    studentMenu(department, name, studentID);
}

// Main function
int main()
{
    int choice;

    do {
        printf("\n================================\n");
        printf("   COLLEGE LIBRARY MANAGEMENT\n");
        printf("================================\n");

        printf("\n1. Admin Login\n");
        printf("2. Student Login\n");
        printf("3. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                adminLogin();
                break;

            case 2:
                studentLogin();
                break;

            case 3:
                printf("\nThank you for using the library!\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while (choice != 3);

    return 0;
}

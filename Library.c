
#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 5

// Department book collections
char *maths[MAX_BOOKS] = {
    "Algebra",
    "Calculus",
    "Statistics",
    "Geometry",
    "Trigonometry"
};

char *physics[MAX_BOOKS] = {
    "Mechanics",
    "Optics",
    "Thermodynamics",
    "Electromagnetism",
    "Quantum Physics"
};

char *chemistry[MAX_BOOKS] = {
    "Organic Chemistry",
    "Inorganic Chemistry",
    "Physical Chemistry",
    "Biochemistry",
    "Analytical Chemistry"
};

// Display books
void displayBooks(char *books[], char department[]) {
    int i;

    printf("\n--- %s Department Books ---\n", department);

    for (i = 0; i < MAX_BOOKS; i++) {
        printf("%d. %s\n", i + 1, books[i]);
    }
}

// Student access
void studentAccess(char department[]) {

    if (strcmp(department, "Maths") == 0) {
        displayBooks(maths, "Maths");
    }
    else if (strcmp(department, "Physics") == 0) {
        displayBooks(physics, "Physics");
    }
    else if (strcmp(department, "Chemistry") == 0) {
        displayBooks(chemistry, "Chemistry");
    }
    else {
        printf("Invalid department!\n");
    }
}

// Admin access
void adminAccess() {

    printf("\nAdmin Access Granted!\n");

    displayBooks(maths, "Maths");
    displayBooks(physics, "Physics");
    displayBooks(chemistry, "Chemistry");
}

int main() {

    int role;
    char department[30];

    printf("===== COLLEGE LIBRARY SYSTEM =====\n");

    printf("\nSelect your role:\n");
    printf("1. Student\n");
    printf("2. Admin\n");

    printf("Enter your choice: ");
    scanf("%d", &role);

    if (role == 1) {

        printf("\nEnter your department (Maths/Physics/Chemistry): ");
        scanf("%29s", department);

        printf("\nStudent Access Granted!\n");

        studentAccess(department);

    }
    else if (role == 2) {

        adminAccess();

    }
    else {

        printf("\nInvalid role!\n");

    }

    return 0;
}

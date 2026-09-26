#include <stdio.h>
#include <string.h>
#include "faculty.h"

static Faculty facultyList[MAX_FACULTY];
static int facultyCount = 0;

static void clearBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addFaculty(void) {
    if (facultyCount >= MAX_FACULTY) {
        printf("\nDatabase full! Cannot add more faculty.\n");
        return;
    }

    Faculty f;

    printf("\nEnter Faculty ID (Numbers only): ");
    if (scanf("%d", &f.id) != 1) {
        printf("Invalid ID input.\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    printf("Enter Name: ");
    if (fgets(f.name, sizeof(f.name), stdin) != NULL) {
        f.name[strcspn(f.name, "\n")] = '\0';
    }

    printf("Enter Department: ");
    if (fgets(f.department, sizeof(f.department), stdin) != NULL) {
        f.department[strcspn(f.department, "\n")] = '\0';
    }

    printf("Enter Subject: ");
    if (fgets(f.subject, sizeof(f.subject), stdin) != NULL) {
        f.subject[strcspn(f.subject, "\n")] = '\0';
    }

    facultyList[facultyCount] = f;
    facultyCount++;

    printf("\nFaculty member added successfully!\n");
}

void viewAllFaculty(void) {
    if (facultyCount == 0) {
        printf("\nNo faculty records found.\n");
        return;
    }

    printf("\n=========================================\n");
    printf("            FACULTY DATABASE             \n");
    printf("=========================================\n");

    for (int i = 0; i < facultyCount; i++) {
        printf("ID        : %d\n", facultyList[i].id);
        printf("Name      : %s\n", facultyList[i].name);
        printf("Department: %s\n", facultyList[i].department);
        printf("Subject   : %s\n", facultyList[i].subject);
        printf("-----------------------------------------\n");
    }
}

void searchFaculty(void) {
    int searchId;

    if (facultyCount == 0) {
        printf("\nNo records available to search.\n");
        return;
    }

    printf("\nEnter Faculty ID to search: ");
    if (scanf("%d", &searchId) != 1) {
        printf("Invalid ID input.\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    for (int i = 0; i < facultyCount; i++) {
        if (facultyList[i].id == searchId) {
            printf("\nFaculty Record Found!\n");
            printf("=========================================\n");
            printf("ID        : %d\n", facultyList[i].id);
            printf("Name      : %s\n", facultyList[i].name);
            printf("Department: %s\n", facultyList[i].department);
            printf("Subject   : %s\n", facultyList[i].subject);
            printf("=========================================\n");
            return;
        }
    }

    printf("\nFaculty with ID %d not found.\n", searchId);
}

void updateFaculty(void) {
    int updateId;

    if (facultyCount == 0) {
        printf("\nNo records available to update.\n");
        return;
    }

    printf("\nEnter Faculty ID to update: ");
    if (scanf("%d", &updateId) != 1) {
        printf("Invalid ID input.\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    for (int i = 0; i < facultyCount; i++) {
        if (facultyList[i].id == updateId) {
            printf("\nTeacher found! Enter new details:\n");

            printf("Enter New Name: ");
            if (fgets(facultyList[i].name, sizeof(facultyList[i].name), stdin) != NULL) {
                facultyList[i].name[strcspn(facultyList[i].name, "\n")] = '\0';
            }

            printf("Enter New Department: ");
            if (fgets(facultyList[i].department, sizeof(facultyList[i].department), stdin) != NULL) {
                facultyList[i].department[strcspn(facultyList[i].department, "\n")] = '\0';
            }

            printf("Enter New Subject: ");
            if (fgets(facultyList[i].subject, sizeof(facultyList[i].subject), stdin) != NULL) {
                facultyList[i].subject[strcspn(facultyList[i].subject, "\n")] = '\0';
            }

            printf("\nFaculty details updated successfully!\n");
            return;
        }
    }

    printf("Faculty with ID %d not found.\n", updateId);
}

void facultyMenu(void) {
    int choice;
    do {
        printf("\n===== FACULTY MODULE =====\n");
        printf("1. Add Faculty\n");
        printf("2. View All Faculty\n");
        printf("3. Search Faculty\n");
        printf("4. Update Faculty\n");
        printf("5. Back / Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            clearBuffer();
            continue;
        }

        switch (choice) {
            case 1: addFaculty(); break;
            case 2: viewAllFaculty(); break;
            case 3: searchFaculty(); break;
            case 4: updateFaculty(); break;
            case 5: printf("\nReturning from Faculty Module...\n"); break;
            default: printf("\nInvalid choice!\n");
        }
    } while (choice != 5);
}

int main(void) {
    facultyMenu();
    return 0;
}

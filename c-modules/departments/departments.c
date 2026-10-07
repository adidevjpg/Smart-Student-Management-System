#include <stdio.h>
#include <string.h>
#include "departments.h"

static void clearBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Check if department code is unique
int isUniqueCode(const Department departments[], int count, const char code[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(departments[i].department_code, code) == 0) {
            return 0; // Not unique
        }
    }
    return 1; // Unique
}

void addDepartment(Department departments[], int *count) {
    if (*count >= MAX_DEPARTMENTS) {
        printf("Department limit reached!\n");
        return;
    }

    printf("\nEnter Department ID: ");
    if (scanf("%d", &departments[*count].department_id) != 1) {
        printf("Invalid Department ID!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    printf("Enter Department Name: ");
    if (fgets(departments[*count].department_name, sizeof(departments[*count].department_name), stdin) != NULL) {
        departments[*count].department_name[strcspn(departments[*count].department_name, "\n")] = '\0';
    }

    printf("Enter Department Code: ");
    if (scanf("%19s", departments[*count].department_code) != 1) {
        printf("Invalid Department Code!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    // Check unique department code
    if (!isUniqueCode(departments, *count, departments[*count].department_code)) {
        printf("Error: Department code already exists!\n");
        return;
    }

    printf("Enter Created Date/Time (e.g. YYYY-MM-DD HH:MM): ");
    if (fgets(departments[*count].created_at, sizeof(departments[*count].created_at), stdin) != NULL) {
        departments[*count].created_at[strcspn(departments[*count].created_at, "\n")] = '\0';
    }

    (*count)++;
    printf("Department added successfully!\n");
}

void displayDepartments(const Department departments[], int count) {
    printf("\n========== DEPARTMENTS ==========\n");

    if (count == 0) {
        printf("No departments found.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nDepartment ID   : %d", departments[i].department_id);
        printf("\nDepartment Name : %s", departments[i].department_name);
        printf("\nDepartment Code : %s", departments[i].department_code);
        printf("\nCreated At      : %s\n", departments[i].created_at);
        printf("---------------------------------");
    }
    printf("\nTotal Departments: %d\n", count);
}

void departmentsMenu(void) {
    Department departments[MAX_DEPARTMENTS];
    int count = 0;
    int choice;

    while (1) {
        printf("\n===== DEPARTMENTS TABLE =====\n");
        printf("1. Add Department\n");
        printf("2. Display Departments\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice!\n");
            clearBuffer();
            continue;
        }

        if (choice == 1) {
            addDepartment(departments, &count);
        } else if (choice == 2) {
            displayDepartments(departments, count);
        } else if (choice == 3) {
            printf("Exiting Departments Module.\n");
            break;
        } else {
            printf("Invalid choice!\n");
        }
    }
}

int main(void) {
    departmentsMenu();
    return 0;
}

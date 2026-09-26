#include <stdio.h>
#include "student.h"

int main(void) {
    int choice;

    while (1) {
        printf("\n==================================\n");
        printf("    STUDENT MANAGEMENT MODULE\n");
        printf("==================================\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                printf("\nExiting Student Module. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Please select an option between 1 and 6.\n");
        }
    }

    return 0;
}

#include <stdio.h>
#include <string.h>
#include "marks.h"

static void clearBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addMark(Marks marks[], int *count) {
    if (*count >= MAX_MARKS) {
        printf("\nError: Marks limit reached!\n");
        return;
    }

    printf("\n--- Add New Mark Record ---\n");

    printf("Enter Mark ID: ");
    if (scanf("%d", &marks[*count].mark_id) != 1) {
        printf("Invalid Mark ID!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    printf("Enter Student ID: ");
    if (scanf("%d", &marks[*count].student_id) != 1) {
        printf("Invalid Student ID!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    printf("Enter Course ID: ");
    if (scanf("%d", &marks[*count].course_id) != 1) {
        printf("Invalid Course ID!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    printf("Enter Marks Obtained: ");
    if (scanf("%f", &marks[*count].marks_obtained) != 1) {
        printf("Invalid marks input!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    printf("Enter Exam Type (e.g. Midterm, Final, Quiz): ");
    if (fgets(marks[*count].exam_type, sizeof(marks[*count].exam_type), stdin) != NULL) {
        marks[*count].exam_type[strcspn(marks[*count].exam_type, "\n")] = '\0';
    }

    printf("Enter Exam Date (DD-MM-YYYY): ");
    if (scanf("%19s", marks[*count].exam_date) != 1) {
        printf("Invalid Date!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    (*count)++;
    printf("\nSuccess: Mark record added successfully!\n");
}

void viewMarks(const Marks marks[], int count) {
    if (count == 0) {
        printf("\nNo marks records found.\n");
        return;
    }

    printf("\n============================== MARKS TABLE ==============================\n");
    printf("%-8s %-12s %-10s %-10s %-15s %-12s\n",
           "Mark ID", "Student ID", "Course ID", "Marks", "Exam Type", "Date");
    printf("-------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-8d %-12d %-10d %-10.2f %-15s %-12s\n",
               marks[i].mark_id,
               marks[i].student_id,
               marks[i].course_id,
               marks[i].marks_obtained,
               marks[i].exam_type,
               marks[i].exam_date);
    }
    printf("=========================================================================\n");
    printf("Total Records: %d\n", count);
}

void marksMenu(void) {
    Marks marks[MAX_MARKS];
    int count = 0;
    int choice;

    while (1) {
        printf("\n===== MARKS MANAGEMENT =====\n");
        printf("1. Add Mark Record\n");
        printf("2. View All Marks\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                addMark(marks, &count);
                break;
            case 2:
                viewMarks(marks, count);
                break;
            case 3:
                printf("\nExiting Marks Module. Goodbye!\n");
                return;
            default:
                printf("\nInvalid choice! Please select 1, 2, or 3.\n");
        }
    }
}

int main(void) {
    marksMenu();
    return 0;
}

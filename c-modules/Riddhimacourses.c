
#include <stdio.h>
#include <string.h>

#define MAX 100

// Structure to store course details
struct Course {
    int courseId;
    char courseName[50];
    char department[50];
    int credits;
};

// Function declarations
int addCourse(struct Course courses[], int count);
int viewCourses(struct Course courses[], int count);
int searchCourse(struct Course courses[], int count, int id);

int main() {
    struct Course courses[MAX];
    int count = 0;
    int choice, id, result;

    do {
        printf("\n===== COURSE MANAGEMENT SYSTEM =====\n");
        printf("1. Add Course\n");
        printf("2. View Courses\n");
        printf("3. Search Course\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                result = addCourse(courses, count);
                if (result == 1) {
                    count++;
                    printf("\nCourse added successfully!\n");
                } else if (result == 0) {
                    printf("\nCourse ID already exists!\n");
                } else {
                    printf("\nCourse limit reached!\n");
                }
                break;

            case 2:
                viewCourses(courses, count);
                break;

            case 3:
                printf("Enter Course ID to search: ");
                scanf("%d", &id);

                result = searchCourse(courses, count, id);

                if (result != -1) {
                    printf("\nCourse Found!\n");
                    printf("Course ID: %d\n",
                           courses[result].courseId);
                    printf("Course Name: %s\n",
                           courses[result].courseName);
                    printf("Department: %s\n",
                           courses[result].department);
                    printf("Credits: %d\n",
                           courses[result].credits);
                } else {
                    printf("\nCourse not found!\n");
                }
                break;

            case 4:
                printf("Exiting Course Module...\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 4);

    return 0;
}

// Function to add a course
int addCourse(struct Course courses[], int count) {
    int id, i;

    if (count >= MAX) {
        return -1;
    }

    printf("Enter Course ID: ");
    scanf("%d", &id);

    // Check for duplicate ID
    for (i = 0; i < count; i++) {
        if (courses[i].courseId == id) {
            return 0;
        }
    }

    courses[count].courseId = id;

    printf("Enter Course Name: ");
    scanf(" %49[^\n]", courses[count].courseName);

    printf("Enter Department: ");
    scanf(" %49[^\n]", courses[count].department);

    printf("Enter Credits: ");
    scanf("%d", &courses[count].credits);

    return 1;
}

// Function to view all courses
int viewCourses(struct Course courses[], int count) {
    int i;

    if (count == 0) {
        printf("\nNo courses available!\n");
        return 0;
    }

    printf("\n========== COURSE DETAILS ==========\n");

    for (i = 0; i < count; i++) {
        printf("\nCourse ID: %d\n", courses[i].courseId);
        printf("Course Name: %s\n", courses[i].courseName);
        printf("Department: %s\n", courses[i].department);
        printf("Credits: %d\n", courses[i].credits);
    }

    return count;
}

// Function to search for a course by ID
int searchCourse(struct Course courses[], int count, int id) {
    int i;

    for (i = 0; i < count; i++) {
        if (courses[i].courseId == id) {
            return i;
        }
    }

    return -1;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "courses.h"

#ifdef USE_MYSQL
#include <mysql.h>
static MYSQL *conn = NULL;

static int connectDatabase(void) {
    conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("MySQL initialization failed!\n");
        return 0;
    }
    if (mysql_real_connect(conn, "localhost", "root", "root", "student_management_system", 3306, NULL, 0) == NULL) {
        printf("Connection failed: %s\n", mysql_error(conn));
        return 0;
    }
    printf("Connected to MySQL successfully!\n");
    return 1;
}
#endif

static void clearBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addCourse(Course courses[], int *count) {
    if (*count >= MAX_COURSES) {
        printf("\nError: Course limit reached!\n");
        return;
    }

    printf("\n--- Add New Course ---\n");

    printf("Enter Course ID: ");
    if (fgets(courses[*count].course_id, sizeof(courses[*count].course_id), stdin) != NULL) {
        courses[*count].course_id[strcspn(courses[*count].course_id, "\n")] = '\0';
    }

    printf("Enter Course Name: ");
    if (fgets(courses[*count].course_name, sizeof(courses[*count].course_name), stdin) != NULL) {
        courses[*count].course_name[strcspn(courses[*count].course_name, "\n")] = '\0';
    }

    printf("Enter Course Code: ");
    if (scanf("%19s", courses[*count].course_code) != 1) {
        printf("Invalid Course Code!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    printf("Enter Department ID: ");
    if (scanf("%d", &courses[*count].department_id) != 1) {
        printf("Invalid Department ID!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    printf("Enter Semester: ");
    if (scanf("%d", &courses[*count].semester) != 1) {
        printf("Invalid Semester!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    printf("Enter Credits: ");
    if (scanf("%d", &courses[*count].credits) != 1) {
        printf("Invalid Credits!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

#ifdef USE_MYSQL
    if (conn != NULL) {
        char query[1000];
        snprintf(query, sizeof(query),
            "INSERT INTO Courses (course_id, course_name, course_code, department_id, semester, credits) "
            "VALUES ('%s', '%s', '%s', %d, %d, %d)",
            courses[*count].course_id, courses[*count].course_name, courses[*count].course_code,
            courses[*count].department_id, courses[*count].semester, courses[*count].credits);
        if (mysql_query(conn, query) != 0) {
            printf("MySQL Warning: %s\n", mysql_error(conn));
        }
    }
#endif

    (*count)++;
    printf("\nSuccess: Course added successfully!\n");
}

void viewCourses(const Course courses[], int count) {
    if (count == 0) {
        printf("\nNo courses available.\n");
        return;
    }

    printf("\n================================== COURSES ==================================\n");
    printf("%-12s %-25s %-12s %-8s %-8s %-8s\n",
           "Course ID", "Course Name", "Code", "Dept ID", "Semester", "Credits");
    printf("-----------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-12s %-25s %-12s %-8d %-8d %-8d\n",
               courses[i].course_id,
               courses[i].course_name,
               courses[i].course_code,
               courses[i].department_id,
               courses[i].semester,
               courses[i].credits);
    }
    printf("=============================================================================\n");
    printf("Total Courses: %d\n", count);
}

void searchCourse(const Course courses[], int count) {
    char search_id[20];

    if (count == 0) {
        printf("\nNo courses to search.\n");
        return;
    }

    printf("\nEnter Course ID to search: ");
    if (fgets(search_id, sizeof(search_id), stdin) != NULL) {
        search_id[strcspn(search_id, "\n")] = '\0';
    }

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(courses[i].course_id, search_id) == 0) {
            printf("\n--- Course Found ---\n");
            printf("Course ID    : %s\n", courses[i].course_id);
            printf("Course Name  : %s\n", courses[i].course_name);
            printf("Course Code  : %s\n", courses[i].course_code);
            printf("Department ID: %d\n", courses[i].department_id);
            printf("Semester     : %d\n", courses[i].semester);
            printf("Credits      : %d\n", courses[i].credits);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nCourse with ID '%s' not found.\n", search_id);
    }
}

void coursesMenu(void) {
    Course courses[MAX_COURSES];
    int count = 0;
    int choice;

    // Default sample courses
    strcpy(courses[0].course_id, "CS101");
    strcpy(courses[0].course_name, "Intro to Programming");
    strcpy(courses[0].course_code, "CSE101");
    courses[0].department_id = 1;
    courses[0].semester = 1;
    courses[0].credits = 4;

    strcpy(courses[1].course_id, "CS102");
    strcpy(courses[1].course_name, "Data Structures");
    strcpy(courses[1].course_code, "CSE102");
    courses[1].department_id = 1;
    courses[1].semester = 2;
    courses[1].credits = 4;
    count = 2;

    while (1) {
        printf("\n--- Courses Management System ---\n");
        printf("1. Add Course\n");
        printf("2. View All Courses\n");
        printf("3. Search Course by ID\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        switch (choice) {
            case 1:
                addCourse(courses, &count);
                break;
            case 2:
                viewCourses(courses, count);
                break;
            case 3:
                searchCourse(courses, count);
                break;
            case 4:
                printf("\nExiting Courses Module. Goodbye!\n");
                return;
            default:
                printf("\nInvalid choice! Please select 1, 2, 3, or 4.\n");
        }
    }
}

int main(void) {
#ifdef USE_MYSQL
    connectDatabase();
#endif
    coursesMenu();
#ifdef USE_MYSQL
    if (conn != NULL) {
        mysql_close(conn);
    }
#endif
    return 0;
}

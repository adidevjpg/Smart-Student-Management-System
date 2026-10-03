#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

#define SIZE 100

MYSQL *conn;

// Structure for Course
struct Course {
    char course_id[20];
    char course_name[50];
    char course_code[20];
    int department_id;
    int semester;
    int credits;
};

// Remove newline from fgets
void removeNewline(char str[]) {
    str[strcspn(str, "\n")] = '\0';
}

// Input string using fgets
void inputString(char str[], int size) {
    fgets(str, size, stdin);
    removeNewline(str);
}

// Connect to MySQL
int connectDatabase() {
    conn = mysql_init(NULL);

    if (conn == NULL) {
        printf("MySQL initialization failed!\n");
        return 0;
    }

    if (mysql_real_connect(conn, "localhost",
        "root", "YOUR_PASSWORD",
        "student_management_system", 3306,
        NULL, 0) == NULL) {

        printf("Connection failed: %s\n",
               mysql_error(conn));
        return 0;
    }

    printf("Connected to MySQL successfully!\n");
    return 1;
}

// Function to add a course
void addCourse() {
    struct Course c;
    char id[41], name[101], code[41];
    char query[1000];

    printf("Enter Course ID: ");
    inputString(c.course_id, sizeof(c.course_id));

    printf("Enter Course Name: ");
    inputString(c.course_name, sizeof(c.course_name));

    printf("Enter Course Code: ");
    inputString(c.course_code, sizeof(c.course_code));

    printf("Enter Department ID: ");
    scanf("%d", &c.department_id);

    printf("Enter Semester: ");
    scanf("%d", &c.semester);

    printf("Enter Credits: ");
    scanf("%d", &c.credits);
    getchar();

    // Escape strings before using them in SQL
    mysql_real_escape_string(conn, id,
        c.course_id, strlen(c.course_id));

    mysql_real_escape_string(conn, name,
        c.course_name, strlen(c.course_name));

    mysql_real_escape_string(conn, code,
        c.course_code, strlen(c.course_code));

    snprintf(query, sizeof(query),
        "INSERT INTO Courses "
        "(course_id, course_name, course_code, "
        "department_id, semester, credits) "
        "VALUES ('%s', '%s', '%s', %d, %d, %d)",
        id, name, code,
        c.department_id, c.semester, c.credits);

    if (mysql_query(conn, query) == 0) {
        printf("Course added successfully!\n");
    } else {
        printf("Error: %s\n", mysql_error(conn));
    }
}

// Function to view all courses
void viewCourses() {
    MYSQL_RES *result;
    MYSQL_ROW row;

    const char *query =
        "SELECT c.course_id, c.course_name, "
        "c.course_code, d.department_name, "
        "c.semester, c.credits, c.created_at "
        "FROM Courses c "
        "JOIN Departments d "
        "ON c.department_id = d.department_id";

    if (mysql_query(conn, query) != 0) {
        printf("Error: %s\n", mysql_error(conn));
        return;
    }

    result = mysql_store_result(conn);

    if (result == NULL) {
        printf("Error: %s\n", mysql_error(conn));
        return;
    }

    if (mysql_num_rows(result) == 0) {
        printf("No courses available.\n");
    }

    while ((row = mysql_fetch_row(result)) != NULL) {
        printf("\nCourse ID: %s\n", row[0]);
        printf("Course Name: %s\n", row[1]);
        printf("Course Code: %s\n", row[2]);
        printf("Department: %s\n", row[3]);
        printf("Semester: %s\n", row[4]);
        printf("Credits: %s\n", row[5]);
        printf("Created At: %s\n", row[6]);
    }

    mysql_free_result(result);
}

// Function to search a course by ID
void searchCourse() {
    char id[20], escapedID[41];
    char query[300];
    MYSQL_RES *result;
    MYSQL_ROW row;

    printf("Enter Course ID to search: ");
    inputString(id, sizeof(id));

    mysql_real_escape_string(conn, escapedID,
        id, strlen(id));

    snprintf(query, sizeof(query),
        "SELECT c.course_id, c.course_name, "
        "c.course_code, d.department_name, "
        "c.semester, c.credits, c.created_at "
        "FROM Courses c "
        "JOIN Departments d "
        "ON c.department_id = d.department_id "
        "WHERE c.course_id = '%s'", escapedID);

    if (mysql_query(conn, query) != 0) {
        printf("Error: %s\n", mysql_error(conn));
        return;
    }

    result = mysql_store_result(conn);

    if (result == NULL) {
        printf("Error: %s\n", mysql_error(conn));
        return;
    }

    if ((row = mysql_fetch_row(result)) != NULL) {
        printf("\nCourse Found!\n");
        printf("Course ID: %s\n", row[0]);
        printf("Course Name: %s\n", row[1]);
        printf("Course Code: %s\n", row[2]);
        printf("Department: %s\n", row[3]);
        printf("Semester: %s\n", row[4]);
        printf("Credits: %s\n", row[5]);
        printf("Created At: %s\n", row[6]);
    } else {
        printf("Course not found!\n");
    }

    mysql_free_result(result);
}

// Main function
int main() {
    int choice;

    if (!connectDatabase()) {
        return 1;
    }

    do {
        printf("\n--- Courses Management System ---\n");
        printf("1. Add Course\n");
        printf("2. View Courses\n");
        printf("3. Search Course\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            mysql_close(conn);
            return 1;
        }
        getchar();

        switch (choice) {
            case 1:
                addCourse();
                break;

            case 2:
                viewCourses();
                break;

            case 3:
                searchCourse();
                break;

            case 4:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 4);

    mysql_close(conn);
    return 0;
}

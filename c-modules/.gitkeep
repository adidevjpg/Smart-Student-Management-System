
#include <stdio.h>
#include <string.h>

#define MAX 100

/* =========================
   DEPARTMENTS TABLE
   ========================= */
typedef struct {
    int department_id;
    char department_name[50];
} Department;


/* =========================
   STUDENTS TABLE
   ========================= */
typedef struct {
    int student_id;
    char student_name[50];

    // Foreign Key
    int department_id;
} Student;


/* =========================
   FACULTY TABLE
   ========================= */
typedef struct {
    int faculty_id;
    char faculty_name[50];

    // Foreign Key
    int department_id;
} Faculty;


/* =========================
   COURSES TABLE
   ========================= */
typedef struct {
    int course_id;
    char course_name[50];

    // Foreign Key
    int department_id;
} Course;


/* =========================
   ATTENDANCE TABLE
   ========================= */
typedef struct {
    int attendance_id;

    // Foreign Keys
    int student_id;
    int course_id;

    char date[15];
    int present;   // 1 = Present, 0 = Absent
} Attendance;


/* =========================
   MARKS TABLE
   ========================= */
typedef struct {
    int marks_id;

    // Foreign Keys
    int student_id;
    int course_id;

    float marks;
} Marks;


/* =========================
   USERS TABLE
   ========================= */
typedef struct {
    int user_id;
    char username[50];
    char password[50];
    char role[20];   // Student / Faculty / Admin
} User;


/* =========================
   MAIN PROGRAM
   ========================= */
int main()
{
    Department departments[MAX];
    Student students[MAX];
    Faculty faculty[MAX];
    Course courses[MAX];
    Attendance attendance[MAX];
    Marks marks[MAX];
    User users[MAX];

    int departmentCount = 0;
    int studentCount = 0;
    int facultyCount = 0;
    int courseCount = 0;
    int attendanceCount = 0;
    int marksCount = 0;
    int userCount = 0;

    int choice;

    do {
        printf("\n========== COLLEGE DATABASE ==========\n");
        printf("1. Add Department\n");
        printf("2. Add Student\n");
        printf("3. Add Faculty\n");
        printf("4. Add Course\n");
        printf("5. Add Attendance\n");
        printf("6. Add Marks\n");
        printf("7. Add User\n");
        printf("8. Display Students\n");
        printf("9. Display Courses\n");
        printf("10. Display Attendance\n");
        printf("11. Display Marks\n");
        printf("0. Exit\n");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        /* =========================
           ADD DEPARTMENT
           ========================= */
        if (choice == 1) {

            printf("Enter Department ID: ");
            scanf("%d", &departments[departmentCount].department_id);

            printf("Enter Department Name: ");
            scanf(" %[^\n]", departments[departmentCount].department_name);

            departmentCount++;

            printf("Department added successfully.\n");
        }

        /* =========================
           ADD STUDENT
           ========================= */
        else if (choice == 2) {

            printf("Enter Student ID: ");
            scanf("%d", &students[studentCount].student_id);

            printf("Enter Student Name: ");
            scanf(" %[^\n]", students[studentCount].student_name);

            printf("Enter Department ID: ");
            scanf("%d", &students[studentCount].department_id);

            studentCount++;

            printf("Student added successfully.\n");
        }

        /* =========================
           ADD FACULTY
           ========================= */
        else if (choice == 3) {

            printf("Enter Faculty ID: ");
            scanf("%d", &faculty[facultyCount].faculty_id);

            printf("Enter Faculty Name: ");
            scanf(" %[^\n]", faculty[facultyCount].faculty_name);

            printf("Enter Department ID: ");
            scanf("%d", &faculty[facultyCount].department_id);

            facultyCount++;

            printf("Faculty added successfully.\n");
        }

        /* =========================
           ADD COURSE
           ========================= */
        else if (choice == 4) {

            printf("Enter Course ID: ");
            scanf("%d", &courses[courseCount].course_id);

            printf("Enter Course Name: ");
            scanf(" %[^\n]", courses[courseCount].course_name);

            printf("Enter Department ID: ");
            scanf("%d", &courses[courseCount].department_id);

            courseCount++;

            printf("Course added successfully.\n");
        }

        /* =========================
           ADD ATTENDANCE
           ========================= */
        else if (choice == 5) {

            printf("Enter Attendance ID: ");
            scanf("%d", &attendance[attendanceCount].attendance_id);

            printf("Enter Student ID: ");
            scanf("%d", &attendance[attendanceCount].student_id);

            printf("Enter Course ID: ");
            scanf("%d", &attendance[attendanceCount].course_id);

            printf("Enter Date (DD-MM-YYYY): ");
            scanf("%s", attendance[attendanceCount].date);

            printf("Present? (1 = Yes, 0 = No): ");
            scanf("%d", &attendance[attendanceCount].present);

            attendanceCount++;

            printf("Attendance added successfully.\n");
        }

        /* =========================
           ADD MARKS
           ========================= */
        else if (choice == 6) {

            printf("Enter Marks ID: ");
            scanf("%d", &marks[marksCount].marks_id);

            printf("Enter Student ID: ");
            scanf("%d", &marks[marksCount].student_id);

            printf("Enter Course ID: ");
            scanf("%d", &marks[marksCount].course_id);

            printf("Enter Marks: ");
            scanf("%f", &marks[marksCount].marks);

            marksCount++;

            printf("Marks added successfully.\n");
        }

        /* =========================
           ADD USER
           ========================= */
        else if (choice == 7) {

            printf("Enter User ID: ");
            scanf("%d", &users[userCount].user_id);

            printf("Enter Username: ");
            scanf("%s", users[userCount].username);

            printf("Enter Password: ");
            scanf("%s", users[userCount].password);

            printf("Enter Role (Student/Faculty/Admin): ");
            scanf("%s", users[userCount].role);

            userCount++;

            printf("User added successfully.\n");
        }

        /* =========================
           DISPLAY STUDENTS
           ========================= */
        else if (choice == 8) {

            printf("\n========== STUDENTS ==========\n");

            for (int i = 0; i < studentCount; i++) {

                printf("\nStudent ID: %d",
                       students[i].student_id);

                printf("\nStudent Name: %s",
                       students[i].student_name);

                printf("\nDepartment ID: %d\n",
                       students[i].department_id);
            }
        }

        /* =========================
           DISPLAY COURSES
           ========================= */
        else if (choice == 9) {

            printf("\n========== COURSES ==========\n");

            for (int i = 0; i < courseCount; i++) {

                printf("\nCourse ID: %d",
                       courses[i].course_id);

                printf("\nCourse Name: %s",
                       courses[i].course_name);

                printf("\nDepartment ID: %d\n",
                       courses[i].department_id);
            }
        }

        /* =========================
           DISPLAY ATTENDANCE
           ========================= */
        else if (choice == 10) {

            printf("\n========== ATTENDANCE ==========\n");

            for (int i = 0; i < attendanceCount; i++) {

                printf("\nAttendance ID: %d",
                       attendance[i].attendance_id);

                printf("\nStudent ID: %d",
                       attendance[i].student_id);

                printf("\nCourse ID: %d",
                       attendance[i].course_id);

                printf("\nDate: %s",
                       attendance[i].date);

                printf("\nStatus: %s\n",
                       attendance[i].present ? "Present" : "Absent");
            }
        }

        /* =========================
           DISPLAY MARKS
           ========================= */
        else if (choice == 11) {

            printf("\n========== MARKS ==========\n");

            for (int i = 0; i < marksCount; i++) {

                printf("\nMarks ID: %d",
                       marks[i].marks_id);

                printf("\nStudent ID: %d",
                       marks[i].student_id);

                printf("\nCourse ID: %d",
                       marks[i].course_id);

                printf("\nMarks: %.2f\n",
                       marks[i].marks);
            }
        }

        else if (choice != 0) {
            printf("Invalid choice!\n");
        }

    } while (choice != 0);

    printf("\nProgram terminated.\n");

    return 0;
}

#include <stdio.h>
#include <string.h>
#include "attendance.h"

/* Calculate attendance percentage */
float calculatePercentage(int held, int attended) {
    if (held == 0) {
        return 0.0f;
    }
    return ((float)attended / (float)held) * 100.0f;
}

/* Find student index by id */
int findStudent(const AttendanceStudent students[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}

/* Find course index by id */
int findCourse(const AttendanceCourse courses[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (courses[i].id == id) {
            return i;
        }
    }
    return -1;
}

int main(void) {
    AttendanceStudent students[MAX_STUDENTS] = {
        {101, "Rahul"},
        {102, "Amit"},
        {103, "Priya"}
    };
    int studentCount = 3;

    AttendanceCourse courses[MAX_COURSES] = {
        {1, "C Programming"},
        {2, "Data Structures"},
        {3, "Mathematics"}
    };
    int courseCount = 3;

    AttendanceRecord attendance[MAX_STUDENTS * MAX_COURSES];
    int attendanceCount = 0;
    int choice;

    while (1) {
        printf("\n====================================\n");
        printf("       ATTENDANCE MANAGEMENT\n");
        printf("====================================\n");
        printf("1. Select Student & Course\n");
        printf("2. Record Attendance\n");
        printf("3. View Attendance\n");
        printf("4. Calculate Attendance Percentage\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        /* -------------------------------- */
        /* Select Student and Course */
        /* -------------------------------- */
        if (choice == 1) {
            int studentId, courseId;

            printf("\nStudents:\n");
            for (int i = 0; i < studentCount; i++) {
                printf("%d - %s\n", students[i].id, students[i].name);
            }

            printf("Enter Student ID: ");
            if (scanf("%d", &studentId) != 1) {
                printf("Invalid Student ID!\n");
                continue;
            }

            int studentIndex = findStudent(students, studentCount, studentId);
            if (studentIndex == -1) {
                printf("Student not found!\n");
                continue;
            }

            printf("\nCourses:\n");
            for (int i = 0; i < courseCount; i++) {
                printf("%d - %s\n", courses[i].id, courses[i].name);
            }

            printf("Enter Course ID: ");
            if (scanf("%d", &courseId) != 1) {
                printf("Invalid Course ID!\n");
                continue;
            }

            int courseIndex = findCourse(courses, courseCount, courseId);
            if (courseIndex == -1) {
                printf("Course not found!\n");
                continue;
            }

            printf("\nSelected Student: %s\n", students[studentIndex].name);
            printf("Selected Course : %s\n", courses[courseIndex].name);
        }

        /* -------------------------------- */
        /* Record Attendance */
        /* -------------------------------- */
        else if (choice == 2) {
            int studentId, courseId;
            char status;

            printf("\nEnter Student ID: ");
            if (scanf("%d", &studentId) != 1) {
                printf("Invalid ID!\n");
                continue;
            }

            if (findStudent(students, studentCount, studentId) == -1) {
                printf("Student not found!\n");
                continue;
            }

            printf("Enter Course ID: ");
            if (scanf("%d", &courseId) != 1) {
                printf("Invalid ID!\n");
                continue;
            }

            if (findCourse(courses, courseCount, courseId) == -1) {
                printf("Course not found!\n");
                continue;
            }

            int index = -1;
            for (int i = 0; i < attendanceCount; i++) {
                if (attendance[i].studentId == studentId && attendance[i].courseId == courseId) {
                    index = i;
                    break;
                }
            }

            if (index == -1) {
                index = attendanceCount;
                attendance[index].studentId = studentId;
                attendance[index].courseId = courseId;
                attendance[index].totalClasses = 0;
                attendance[index].attendedClasses = 0;
                attendanceCount++;
            }

            if (attendance[index].totalClasses >= MAX_CLASSES) {
                printf("Maximum class limit reached!\n");
                continue;
            }

            printf("Enter attendance (P = Present, A = Absent): ");
            scanf(" %c", &status);

            if (status != 'P' && status != 'p' && status != 'A' && status != 'a') {
                printf("Invalid attendance status!\n");
                continue;
            }

            if (status == 'p') status = 'P';
            if (status == 'a') status = 'A';

            attendance[index].status[attendance[index].totalClasses] = status;
            attendance[index].totalClasses++;

            if (status == 'P') {
                attendance[index].attendedClasses++;
            }

            printf("Attendance recorded successfully!\n");
        }

        /* -------------------------------- */
        /* View Attendance */
        /* -------------------------------- */
        else if (choice == 3) {
            int studentId, courseId;

            printf("\nEnter Student ID: ");
            if (scanf("%d", &studentId) != 1) {
                printf("Invalid ID!\n");
                continue;
            }

            printf("Enter Course ID: ");
            if (scanf("%d", &courseId) != 1) {
                printf("Invalid ID!\n");
                continue;
            }

            int studentIndex = findStudent(students, studentCount, studentId);
            int courseIndex = findCourse(courses, courseCount, courseId);

            if (studentIndex == -1 || courseIndex == -1) {
                printf("Invalid Student ID or Course ID!\n");
                continue;
            }

            int index = -1;
            for (int i = 0; i < attendanceCount; i++) {
                if (attendance[i].studentId == studentId && attendance[i].courseId == courseId) {
                    index = i;
                    break;
                }
            }

            if (index == -1) {
                printf("\nNo attendance recorded yet.\n");
                continue;
            }

            printf("\n====================================\n");
            printf("Student ID      : %d\n", studentId);
            printf("Student Name    : %s\n", students[studentIndex].name);
            printf("Course          : %s\n", courses[courseIndex].name);
            printf("Classes Held    : %d\n", attendance[index].totalClasses);
            printf("Classes Attended: %d\n", attendance[index].attendedClasses);
            printf("Attendance      : %.2f%%\n",
                   calculatePercentage(attendance[index].totalClasses, attendance[index].attendedClasses));
            printf("Status History  : ");

            for (int i = 0; i < attendance[index].totalClasses; i++) {
                printf("%c ", attendance[index].status[i]);
            }
            printf("\n====================================\n");
        }

        /* -------------------------------- */
        /* Calculate Percentage */
        /* -------------------------------- */
        else if (choice == 4) {
            int studentId, courseId;

            printf("\nEnter Student ID: ");
            if (scanf("%d", &studentId) != 1) {
                printf("Invalid ID!\n");
                continue;
            }

            printf("Enter Course ID: ");
            if (scanf("%d", &courseId) != 1) {
                printf("Invalid ID!\n");
                continue;
            }

            int index = -1;
            for (int i = 0; i < attendanceCount; i++) {
                if (attendance[i].studentId == studentId && attendance[i].courseId == courseId) {
                    index = i;
                    break;
                }
            }

            if (index == -1) {
                printf("\nNo attendance data found.\n");
                continue;
            }

            float percentage = calculatePercentage(attendance[index].totalClasses, attendance[index].attendedClasses);

            printf("\nStudent ID      : %d\n", studentId);
            printf("Classes Held    : %d\n", attendance[index].totalClasses);
            printf("Classes Attended: %d\n", attendance[index].attendedClasses);
            printf("Attendance      : %.2f%%\n", percentage);
        }

        /* -------------------------------- */
        /* Exit */
        /* -------------------------------- */
        else if (choice == 5) {
            printf("\nExiting Attendance Module. Goodbye!\n");
            break;
        } else {
            printf("\nInvalid choice!\n");
        }
    }

    return 0;
}

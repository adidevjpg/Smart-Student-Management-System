#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#define MAX_STUDENTS 50
#define MAX_COURSES 10
#define MAX_CLASSES 100

typedef struct {
    int id;
    char name[50];
} AttendanceStudent;

typedef struct {
    int id;
    char name[50];
} AttendanceCourse;

typedef struct {
    int studentId;
    int courseId;
    int totalClasses;
    int attendedClasses;
    char status[MAX_CLASSES]; // 'P' = Present, 'A' = Absent
} AttendanceRecord;

float calculatePercentage(int held, int attended);
int findStudent(const AttendanceStudent students[], int count, int id);
int findCourse(const AttendanceCourse courses[], int count, int id);

#endif /* ATTENDANCE_H */

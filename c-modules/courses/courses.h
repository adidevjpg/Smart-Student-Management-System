#ifndef COURSES_H
#define COURSES_H

#define MAX_COURSES 100

typedef struct {
    char course_id[20];
    char course_name[50];
    char course_code[20];
    int department_id;
    int semester;
    int credits;
} Course;

void addCourse(Course courses[], int *count);
void viewCourses(const Course courses[], int count);
void searchCourse(const Course courses[], int count);
void coursesMenu(void);

#endif /* COURSES_H */

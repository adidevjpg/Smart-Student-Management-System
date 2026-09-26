#ifndef STUDENT_H
#define STUDENT_H

#define DATA_FILE "students.dat"
#define TEMP_FILE "temp_students.dat"

typedef struct {
    int student_id;
    char name[100];
    int department_id;
} Student;

int isDuplicateId(int student_id);
void clearInputBuffer(void);
void addStudent(void);
void viewStudents(void);
void searchStudent(void);
void updateStudent(void);
void deleteStudent(void);

#endif /* STUDENT_H */

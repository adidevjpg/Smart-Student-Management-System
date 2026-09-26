#ifndef FACULTY_H
#define FACULTY_H

#define MAX_FACULTY 100

typedef struct {
    int id;
    char name[50];
    char department[50];
    char subject[50];
} Faculty;

void addFaculty(void);
void viewAllFaculty(void);
void searchFaculty(void);
void updateFaculty(void);
void facultyMenu(void);

#endif /* FACULTY_H */

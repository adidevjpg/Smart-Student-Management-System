#ifndef FACULTY_H
#define FACULTY_H

#define MAX_FACULTY 100

struct Faculty {
    int id;
    char name[50];
    char department[50];
    char subject[50];
};

void addFaculty();
void viewAllFaculty();
void searchFaculty();
void updateFaculty();
void facultyMenu(); 

#endif


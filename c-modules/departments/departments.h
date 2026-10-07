#ifndef DEPARTMENTS_H
#define DEPARTMENTS_H

#define MAX_DEPARTMENTS 100

typedef struct {
    int department_id;
    char department_name[100];
    char department_code[20];
    char created_at[30];
} Department;

int isUniqueCode(const Department departments[], int count, const char code[]);
void addDepartment(Department departments[], int *count);
void displayDepartments(const Department departments[], int count);
void departmentsMenu(void);

#endif /* DEPARTMENTS_H */

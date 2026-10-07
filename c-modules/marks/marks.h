#ifndef MARKS_H
#define MARKS_H

#define MAX_MARKS 100

typedef struct {
    int mark_id;
    int student_id;
    int course_id;
    float marks_obtained;
    char exam_type[50];
    char exam_date[20];
} Marks;

void addMark(Marks marks[], int *count);
void viewMarks(const Marks marks[], int count);
void marksMenu(void);

#endif /* MARKS_H */

#include <stdio.h>
#include <string.h>
#include "faculty.h" 

struct Faculty facultyList[MAX_FACULTY];
int facultyCount = 0;

void addFaculty() {
    if (facultyCount >= MAX_FACULTY) {
        printf("\n? Database full! Cannot add more faculty.\n");
        return;
    }

    struct Faculty f;
    
    
    while (getchar() != '\n'); 

    printf("\nEnter Faculty ID (Numbers only): ");
    scanf("%d", &f.id);
    

    while (getchar() != '\n'); 

    printf("Enter Name: ");
    fgets(f.name, sizeof(f.name), stdin);
    f.name[strcspn(f.name, "\n")] = 0; 

    printf("Enter Department: ");
    fgets(f.department, sizeof(f.department), stdin);
    f.department[strcspn(f.department, "\n")] = 0;

    printf("Enter Subject: ");
    fgets(f.subject, sizeof(f.subject), stdin);
    f.subject[strcspn(f.subject, "\n")] = 0;

    facultyList[facultyCount] = f;
    facultyCount++;

    printf("\n Faculty member added successfully!\n");
    
    
    printf("Press Enter to continue...");
    getchar();
}

    


void viewAllFaculty() {
	int i;
    if (facultyCount == 0) {
        printf("\n?? No faculty records found.\n");
        printf("\nPress [ENTER] to return to menu...");
        fflush(stdin); 
        getchar();     
        return;
    }

    printf("\n=========================================\n");
    printf("            FACULTY DATABASE             \n");
    printf("=========================================\n");
    
    for ( i = 0; i < facultyCount; i++) {
        printf("ID: %d\n", facultyList[i].id);
        printf("Name: %s\n", facultyList[i].name);
        printf("Department: %s\n", facultyList[i].department);
        printf("Subject: %s\n", facultyList[i].subject);
        printf("-----------------------------------------\n");
    }


    printf("\nPress [ENTER] to return to menu...");
    fflush(stdin); 
    getchar();    
}

    

void searchFaculty() {
    int i; 
    int searchId;

    if (facultyCount == 0) {
        printf("\n No records available to search.\n");
        printf("\nPress [ENTER] to return to menu...");
        while (getchar() != '\n'); 
        getchar();
        return;
    }

    while (getchar() != '\n'); 

    printf("\nEnter Faculty ID to search: ");
    if (scanf("%d", &searchId) != 1) {
        printf("? Invalid ID input.\n");
        return;
    }

    
    for (i = 0; i < facultyCount; i++) {
        if (facultyList[i].id == searchId) {
            printf("\n Faculty Record Found!\n");
            printf("=========================================\n");
            printf("ID: %d\n", facultyList[i].id);
            printf("Name: %s\n", facultyList[i].name);
            printf("Department: %s\n", facultyList[i].department);
            printf("Subject: %s\n", facultyList[i].subject);
            printf("=========================================\n");
            
            printf("\nPress [ENTER] to return to menu...");
            while (getchar() != '\n'); 
            getchar();                
            return;
        }
    }
    
    printf("\n Faculty with ID %d not found.\n", searchId);
    printf("\nPress [ENTER] to return to menu...");
    while (getchar() != '\n'); 
    getchar();

}

void updateFaculty() {
    int i; 
    int updateId;

    if (facultyCount == 0) {
        printf("\n No records available to update.\n");
        printf("\nPress [ENTER] to return to menu...");
        while (getchar() != '\n'); 
        getchar();
        return;
    }
    while (getchar() != '\n'); 

    printf("\nEnter Faculty ID to update: ");
    if (scanf("%d", &updateId) != 1) {
        printf(" Invalid ID input.\n");
        return;
    }


    for (i = 0; i < facultyCount; i++) {
        if (facultyList[i].id == updateId) {
            printf("\nTeacher found! Enter new details:\n");
            
            while (getchar() != '\n'); 

            printf("Enter New Name: ");
            fgets(facultyList[i].name, sizeof(facultyList[i].name), stdin);
            facultyList[i].name[strcspn(facultyList[i].name, "\n")] = 0;

            printf("Enter New Department: ");
            fgets(facultyList[i].department, sizeof(facultyList[i].department), stdin);
            facultyList[i].department[strcspn(facultyList[i].department, "\n")] = 0;

            printf("Enter New Subject: ");
            fgets(facultyList[i].subject, sizeof(facultyList[i].subject), stdin);
            facultyList[i].subject[strcspn(facultyList[i].subject, "\n")] = 0;

            printf("\n Faculty details updated successfully!\n");
            

            printf("\nPress [ENTER] to return to menu...");
            getchar(); 
            return;
        }
    }
    
    printf(" Faculty with ID %d not found.\n", updateId);
    printf("\nPress [ENTER] to return to menu...");
    while (getchar() != '\n');
    getchar();
}
    
void facultyMenu() {
    int choice;
    do {
        printf("\n===== FACULTY MODULE =====\n");
        printf("1. Add Faculty\n");
        printf("2. View All Faculty\n");
        printf("3. Search Faculty\n");
        printf("4. Update Faculty\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addFaculty(); break;
            case 2: viewAllFaculty(); break;
            case 3: searchFaculty(); break;
            case 4: updateFaculty(); break;
            case 5: printf("\nReturning to Main Menu...\n"); break;
            default: printf("\n Invalid choice!\n");
        }
    } while (choice != 5);
}


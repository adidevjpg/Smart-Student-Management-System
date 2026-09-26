#include <stdio.h>
#include <string.h>
#include "auth.h"

static User users[MAX_USERS];
static int userCount = 0;

// Function to create default users
void createDefaultUsers(void) {
    users[0].userId = 1;
    strcpy(users[0].username, "admin");
    strcpy(users[0].password, "admin123");
    strcpy(users[0].role, "Admin");

    users[1].userId = 2;
    strcpy(users[1].username, "student");
    strcpy(users[1].password, "student123");
    strcpy(users[1].role, "Student");

    users[2].userId = 3;
    strcpy(users[2].username, "faculty");
    strcpy(users[2].password, "faculty123");
    strcpy(users[2].role, "Faculty");

    userCount = 3;
}

// Function to add a new user
void addUser(void) {
    if (userCount >= MAX_USERS) {
        printf("User limit reached!\n");
        return;
    }

    users[userCount].userId = userCount + 1;

    printf("\nEnter Username: ");
    scanf("%29s", users[userCount].username);

    printf("Enter Password: ");
    scanf("%29s", users[userCount].password);

    printf("Enter Role (Admin/Student/Faculty): ");
    scanf("%19s", users[userCount].role);

    userCount++;

    printf("\nUser added successfully!\n");
}

// Function to display all users
void viewUsers(void) {
    printf("\n---------- USER LIST ----------\n");
    printf("%-10s %-20s %-20s %-15s\n",
           "User ID", "Username", "Password", "Role");

    for (int i = 0; i < userCount; i++) {
        printf("%-10d %-20s %-20s %-15s\n",
               users[i].userId,
               users[i].username,
               users[i].password,
               users[i].role);
    }
}

// Login verification
int login(void) {
    char username[30];
    char password[30];

    printf("\n========== LOGIN ==========\n");
    printf("Username: ");
    scanf("%29s", username);

    printf("Password: ");
    scanf("%29s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 &&
            strcmp(password, users[i].password) == 0) {
            printf("\nLogin successful!\n");
            printf("Welcome, %s!\n", users[i].username);
            printf("Role: %s\n", users[i].role);
            return 1;
        }
    }

    printf("\nInvalid username or password!\n");
    return 0;
}

// Main function for authentication module
int main(void) {
    int choice;
    int loginStatus;

    createDefaultUsers();

    do {
        printf("\n===== USER MANAGEMENT =====\n");
        printf("1. Login\n");
        printf("2. Add User\n");
        printf("3. View Users\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        switch (choice) {
            case 1:
                loginStatus = login();
                if (loginStatus) {
                    printf("\nAccess granted to Main Menu.\n");
                }
                break;
            case 2:
                addUser();
                break;
            case 3:
                viewUsers();
                break;
            case 4:
                printf("\nExiting User Module...\n");
                break;
            default:
                printf("\nInvalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}

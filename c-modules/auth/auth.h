#ifndef AUTH_H
#define AUTH_H

#define MAX_USERS 100

typedef struct {
    int userId;
    char username[30];
    char password[30];
    char role[20];
} User;

void createDefaultUsers(void);
void addUser(void);
void viewUsers(void);
int login(void);

#endif /* AUTH_H */

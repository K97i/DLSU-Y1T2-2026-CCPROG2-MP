/*

    user_array_operations.c

    Contains the login and register menus

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-27-2026

*/

#include <string.h>

#include "search_and_sort.h"
#include "user_struct.h"
#include "file_operation.h"

void addUser(UserData *userData, User *user) {
    userData->users[userData->currentUserCount] = *user;
    userData->currentUserCount++;
    UserSort(userData);
    setUsers(userData);
}

void updateUser(UserData *userData, User *user) {
    int flag = 0;

    for (int i = 0 ; i < userData->currentUserCount && !flag ; i++) {
        if (!strcmp(userData->users[i].username, user->username)) {
            userData->users[i] = *user;
            flag = 1;
        }
    }
    setUsers(userData);
}

void removeUser(UserData *userData, User *user) {
    int count = 0;

    for (int i = 0 ; i < userData->currentUserCount ; i++) {
        if (!strcmp(userData->users[i].username, user->username))
            count++;

        userData->users[i] = userData->users[i + count];
    }
    setUsers(userData);
}
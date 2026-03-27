/*

    user_array_operations.h

    Header file for user_array_operations.c

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-27-2026

*/

#ifndef USER_ARRAY_OPERATIONS
#define USER_ARRAY_OPERATIONS

#include "user_struct.h"

void addUser(UserData *userData, User *user);
void updateUser(UserData *userData, User *user);
void removeUser(UserData *userData, User *user);

#endif
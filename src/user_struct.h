/*

    user_struct.h

    Header file to define the User struct

    Author: EBORDE, Mikaelo D.
    Last Modified: 2-28-2026

*/

#ifndef USER_STRUCT
#define USER_STRUCT

#define USER_LIMIT 200 // 200 maximum users can be registered
#define UN_PW_LENGTH 32 // 31 characters + null

typedef struct {
    char username[UN_PW_LENGTH];
    char password[UN_PW_LENGTH];
    int administrator;
} User;

#endif
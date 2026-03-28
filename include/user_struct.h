/*

    user_struct.h

    Header file to define the User struct

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-28-2026

*/

#ifndef USER_STRUCT
#define USER_STRUCT

#include "species_struct.h"

#define USER_LIMIT 50 // 50 maximum users can be registered
#define UN_PW_LENGTH 31 // 30 characters + null

typedef struct {
	Species species[SPECIES_LIMIT];
    char username[UN_PW_LENGTH];
    char password[UN_PW_LENGTH];
    int currentSpeciesCount;
    int administrator;
} User;

// to save to database
typedef struct {
    User users[USER_LIMIT];
    int currentUserCount;
} UserData;

#endif
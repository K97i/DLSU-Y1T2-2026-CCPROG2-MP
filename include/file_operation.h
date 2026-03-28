/*

    file_operations.h

    Header file for file_operations.c to use in other parts of the program

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-27-2026

*/

#ifndef FILE_OPERATIONS
#define FILE_OPERATIONS

#include "config_struct.h"
#include "user_struct.h"

Config getConfig();
int setConfig(Config configWrite);
int resetConfig();

void getUsers(UserData *userData);
int setUsers(const UserData *userData);

void getSpecies(SDB *sDB);
int setSpecies(SDB *sDB);

#endif
/*

    account_operations.h

    Header file for account_operations.c

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-29-2026

*/

#ifndef ACCOUNT_OPTIONS
#define ACCOUNT_OPTIONS

#include "user_struct.h"
#include "species_struct.h"
#include "config_struct.h"

int accountMenu(UserData *userData, int userIndex, Config *config, SDB *sDB);

#endif
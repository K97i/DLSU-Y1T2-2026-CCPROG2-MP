/*

    login_register.h

    Header file for login_register.c

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-27-2026

*/

#ifndef LOGIN_REGISTER
#define LOGIN_REGISTER

#include "user_struct.h"
#include "config_struct.h"

void loginMenu(UserData *userData, Config *config);
void registerMenu(UserData *userData, Config *config);
void resetPasswordMenu(UserData *userData, Config *config);

#endif
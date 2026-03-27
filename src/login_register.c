/*

    login_register.c

    Contains the login and register menus

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-27-2026

*/

#include <stdio.h>
#include <string.h>

#include "config_struct.h"
#include "user_struct.h"
#include "string_helpers.h"
#include "search_and_sort.h"
#include "encryption.h"
#include "file_operation.h"

#define BANNED_WORDS_LIST 2

int checkIfBanned(char input[UN_PW_LENGTH]) {
    char bannedWords[BANNED_WORDS_LIST][UN_PW_LENGTH] = {
        "[EXIT]", " , "
    };
    int flag = 0;

    // for each banned word...
    for (int i = 0 ; i < BANNED_WORDS_LIST && !flag ; i++) {
        // for each substring...
        for (int j = 0 ; j < strlen(input) - strlen(bannedWords[i] - 1) && !flag ; j++) {
            // if substring matches banned word...
            if (!strncmp(input + j, bannedWords[i], strlen(bannedWords[i]))) {
                flag = 1;
            }
        }
    }

    return flag;
}

void loginMenu(UserData *userData, Config *config) {
    User user = { 0 }, retrieved = { 0 };
    char temp[UN_PW_LENGTH] = "";
    int unFlag = 0, pwFlag = 0, exitFlag = 0, failCounter = 3;

    printf("=== [ LOGIN ] ===\n\n");
    printf("Enter \"[EXIT]\" to exit this menu at any time.\n");

    while (!unFlag && !exitFlag) {
        printf("Enter Username: ");
        safeStringScanf(user.username, UN_PW_LENGTH);

        if (!strcmp("[EXIT]", user.username))
            exitFlag = 1;

        else if (UserSearch(*userData, user.username, &retrieved))
            unFlag = 1;

        else
            printf("Username not found!\n");
    }

    while (!pwFlag && !exitFlag) {

        printf("Enter Password: ");
        safeStringScanf(temp, UN_PW_LENGTH);
        encrypt(temp, user.username, config, user.password);

        if (!strcmp("[EXIT]", temp))
            exitFlag = 1;

        else if (!strcmp(user.password, retrieved.password))
            user = retrieved;

        else {
            if (failCounter > 0) {
                printf("Incorrect password! %d attempts remaining.\n", failCounter);
                failCounter--;
            }

            else {
                printf("Login Failed! Please try again.\n");
                exitFlag = 1;
            }
            
        }

    }

    if (unFlag && pwFlag && !exitFlag) {
        printf("Logged in.\n");

        if (user.administrator) {
            // adminMenu(userData, &user); 
        }

        else {
            // userMenu(userData, &user);
        }
    }
}

void registerMenu(UserData *userData, Config *config) {

    if (userData->currentUserCount < USER_LIMIT) {
        User user = { 0 };
        char temp[UN_PW_LENGTH] = "", select = '\0';
        int unFlag = 0, pwFlag = 0, exitFlag = 0, adminFlag = 0;

        printf("=== [ REGISTER ] ===\n\n");
        printf("Enter \"[EXIT]\" to exit this menu at any time.\n");

        while (!unFlag && !exitFlag) {

            printf("Enter Username: ");
            safeStringScanf(user.username, UN_PW_LENGTH);
            
            if (!strcmp("[EXIT]", user.username))
                exitFlag = 1;

            else if (checkIfBanned(user.username))
                printf("Invalid Username! (part of banned words list)\n");

            else
                unFlag = 1;

        }

        while (!pwFlag && !exitFlag) {

            printf("Enter Password: ");
            safeStringScanf(temp, UN_PW_LENGTH);

            if (!strcmp("[EXIT]", temp))
                exitFlag = 1;

            else if (checkIfBanned(temp))
                printf("Invalid Password! (part of banned words list)\n");

            else {
                encrypt(temp, user.username, config, user.password);
                printf("Confirm password: ");
                safeStringScanf(temp, UN_PW_LENGTH);
                encrypt(temp, user.username, config, temp);

                if (!strcmp(user.password, temp)){
                    pwFlag = 1;
                    printf("Confirmation success!\n");
                }

                else if (!strcmp("[EXIT]", temp))
                    exitFlag = 1;

                else
                    printf("Confirmation mismatch!\n");
            }

        }

        while (!adminFlag && !exitFlag) {
            printf("Register as admin? (y / N): ");
            safeCharScanf(&select);

            if (select == 'Y' || select == 'y') {
                printf("Enter override key: ");
                safeStringScanf(temp, CONFIG_STRING_LEN);

                if (!strcmp(temp, config->administratorKey)){
                    user.administrator = 1;
                    printf("Admin priviliges granted.\n");
                    printf("Registering as admin...\n");
                }

                else {
                    user.administrator = 0;
                    printf("Admin privileges denied.\n");
                    printf("Registering as normal user...\n");
                }
            }

            else {
                user.administrator = 0;
                printf("Registering as normal user...\n");
            }

            printf("Registered! Login to account to use Chardex.\n");
            adminFlag = 1;
            
        }

        // AddUser(userData, &user);
    }
    
    else {
        printf("Sorry! Maximum amount of users are registered.\n");
    }
}
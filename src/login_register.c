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
#include "user_array_operations.h"
#include "user_menu.h"
#include "species_struct.h"

void loginMenu(UserData *userData, Config *config) {
    if (userData->currentUserCount < 1) {
        printf("No users registered!\n");
    }

    else {
        char temp[UN_PW_LENGTH] = "";
        int unFlag = 0, pwFlag = 0, exitFlag = 0, failCounter = 3, index = -1;

        printf("=== [ LOGIN ] ===\n\n");
        printf("Enter \"[EXIT]\" to exit this menu at any time.\n");

        while (!unFlag && !exitFlag) {
            printf("Enter Username: ");
            safeStringScanf(temp, UN_PW_LENGTH);
            index = UserSearch(userData, temp);

            if (!strcmp("[EXIT]", temp))
                exitFlag = 1;

            else if (index != -1)
                unFlag = 1;

            else
                printf("Username not found!\n");
        }

        while (!pwFlag && !exitFlag) {

            printf("Enter Password: ");
            safeStringScanf(temp, UN_PW_LENGTH);
            encrypt(temp, config, temp);

            if (!strcmp("[EXIT]", temp))
                exitFlag = 1;

            else if (!strcmp(userData->users[index].password, temp))
                pwFlag = 1;

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
            printf("Logged in.\n\n");

            SDB sDB;
            getSpecies(&sDB);

            if (userData->users[index].administrator) {
                adminMenu(userData, index, &sDB); 
            }

            else {
                userMenu(userData, index, &sDB);
            }
        }

        printf("\n");
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
            safeStringScanf(temp, UN_PW_LENGTH);
            
            if (!strcmp("[EXIT]", temp))
                exitFlag = 1;

            else if (checkIfBanned(temp, UN_PW_LENGTH))
                printf("Invalid Username! (part of banned words list)\n");

            else if (UserSearch(userData, temp) != -1)
                printf("User already exists!\n");

            else{
                strcpy(user.username, temp);
                unFlag = 1;
            }

        }

        while (!pwFlag && !exitFlag) {

            printf("Enter Password: ");
            safeStringScanf(temp, UN_PW_LENGTH);

            if (!strcmp("[EXIT]", temp))
                exitFlag = 1;

            else if (checkIfBanned(temp, UN_PW_LENGTH))
                printf("Invalid Password! (part of banned words list)\n");

            else if (!strcmp(user.username, temp))
                printf("Invalid Password! (password cannot be the same as the username)\n");

            else {
                encrypt(temp, config, user.password);
                
                printf("Confirm password: ");
                safeStringScanf(temp, UN_PW_LENGTH);
                
                encrypt(temp, config, temp);

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

            addUser(userData, &user);
            printf("Registered! Login to account to use Chardex.\n");
            adminFlag = 1;
            
        }

    }
    
    else {
        printf("Sorry! Maximum amount of users are registered.\n");
    }

    printf("\n");
}

void resetPasswordMenu(UserData *userData, Config *config) {
    if (userData->currentUserCount < 1) {
        printf("No users registered!\n");
    }

    else {
        char temp[UN_PW_LENGTH] = "", encrypted[UN_PW_LENGTH] = "";
        int unFlag = 0, overrideFlag = 0, pwFlag = 0, exitFlag = 0, index = -1;

        printf("=== [ PASSWORD RESET ] ===\n\n");
        printf("Enter \"[EXIT]\" to exit this menu at any time.\n");

        while (!unFlag && !exitFlag) {
            printf("Enter Username: ");
            safeStringScanf(temp, UN_PW_LENGTH);
            index = UserSearch(userData, temp);

            if (!strcmp("[EXIT]", temp))
                exitFlag = 1;

            else if (index != -1)
                unFlag = 1;

            else
                printf("Username not found!\n");
        }

        while (!overrideFlag && !exitFlag) {
            printf("Enter override key: ");
            safeStringScanf(temp, CONFIG_STRING_LEN);

            if (!strcmp("[EXIT]", temp))
                exitFlag = 1;

            else if (!strcmp(temp, config->administratorKey))
                overrideFlag = 1;

            else {
                printf("Invalid override key!\n");
            }
            
        }

        if (unFlag && overrideFlag && !exitFlag) {
            while (!pwFlag && !exitFlag) {

                printf("Enter Password: ");
                safeStringScanf(temp, UN_PW_LENGTH);
                encrypt(temp, config, encrypted);

                if (!strcmp("[EXIT]", temp))
                    exitFlag = 1;

                else if (checkIfBanned(temp, UN_PW_LENGTH))
                    printf("Invalid Password! (part of banned words list)\n");

                else if (!strcmp(userData->users[index].username, temp))
                    printf("Invalid Password! (password cannot be the same as the username)\n");

                else if (!strcmp(userData->users[index].password, encrypted))
                    printf("Invalid Password! (password cannot be the same as the old password)\n");

                else {
                    printf("Confirm password: ");
                    safeStringScanf(temp, UN_PW_LENGTH);
                    encrypt(temp, config, temp);

                    if (!strcmp(userData->users[index].password, temp)){
                        strcpy(userData->users[index].password, temp);
                        setUsers(userData);
                        pwFlag = 1;
                        printf("Confirmation success!\n");
                        printf("Password reset successful! Login to Chardex using the new password.\n");
                    }

                    else if (!strcmp("[EXIT]", temp))
                        exitFlag = 1;

                    else
                        printf("Confirmation mismatch!\n");
                }

            }

        }

    }
}
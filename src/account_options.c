/*

    account_operations.c

    Contains the menu to modify account details

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-29-2026

*/

#include <stdio.h>
#include <string.h>

#include "user_struct.h"
#include "species_struct.h"
#include "config_struct.h"
#include "file_operation.h"
#include "search_and_sort.h"
#include "string_helpers.h"
#include "encryption.h"

void updatePokedexOnDelete(UserData *userData, int userIndex, SDB *sDB) {
    int searchDB = -1;
    
    for (int i = 0 ; i < userData->users[userIndex].currentSpeciesCount ; i++) {
        searchDB = SpeciesDataBaseSearch(sDB, userData->users[userIndex].species[i].name);
        
        if (searchDB != 1)
            sDB->species[searchDB].userInputCount--;
    }
}

void deleteAccountFromDB(UserData *userData, int userIndex) {
    for (int i = userIndex ; i < userData->currentUserCount ; i++)
        userData->users[i] = userData->users[i + 1];
}

int changePassword(UserData *userData, int userIndex, Config *config) {
    char temp[UN_PW_LENGTH] = "", encrypted[UN_PW_LENGTH] = "";
    int oldPWFlag = 0, newPWFlag = 0, exitFlag = 0;

    while (!oldPWFlag && !exitFlag) {
        printf("Enter old password: ");
        safeStringScanf(temp, UN_PW_LENGTH);
        encrypt(temp, config, temp);

        if (!strcmp("[EXIT]", temp))
            exitFlag = 1;

        else if (!strcmp(temp, userData->users[userIndex].password))
            oldPWFlag = 1;

        else {
            printf("Password does not match!\n");
        }
        
    }

    if (oldPWFlag && !exitFlag) {
        while (!newPWFlag && !exitFlag) {

            printf("Enter Password: ");
            safeStringScanf(temp, UN_PW_LENGTH);
            encrypt(temp, config, encrypted);

            if (!strcmp("[EXIT]", temp))
                exitFlag = 1;

            else if (checkIfBanned(temp, UN_PW_LENGTH))
                printf("Invalid Password! (part of banned words list)\n");

            else if (!strcmp(userData->users[userIndex].username, temp))
                printf("Invalid Password! (password cannot be the same as the username)\n");

            else if (!strcmp(userData->users[userIndex].password, encrypted))
                printf("Invalid Password! (password cannot be the same as the old password)\n");

            else {
                printf("Confirm password: ");
                safeStringScanf(temp, UN_PW_LENGTH);
                encrypt(temp, config, temp);

                if (!strcmp(temp, encrypted)){
                    strcpy(userData->users[userIndex].password, encrypted);
                    setUsers(userData);
                    newPWFlag = 1;
                    printf("Confirmation success!\n");
                    printf("Password change successful! Login again using the new password.\n");
                }

                else if (!strcmp("[EXIT]", temp))
                    exitFlag = 1;

                else
                    printf("Confirmation mismatch!\n");
            }

        }

    }

    return newPWFlag;
}

int deleteAccount(UserData *userData, int userIndex, Config *config, SDB *sDB) {
    char overrideTemp[CONFIG_STRING_LEN] = "";
    int firstConfirmation = 0, secondConfirmation = 0, overrideFlag = 0,
        exitFlag = 0, select = 0, returnFlag = 0;

    while (!firstConfirmation && !exitFlag) {
        printf("Delete account?\n");
        printf("[1] Confirm\n");
        printf("[2] Cancel\n");
        select = menuInputInt(1, 2);

        switch (select) {
            case 1: 
                firstConfirmation = 1;
                break;

            case 2: 
                exitFlag = 1;
                break;
        }
    }

    while (!secondConfirmation && !exitFlag) {
        printf("Last warning! This is irreversible! Confirm?\n");
        printf("[1] Confirm\n");
        printf("[2] Cancel\n");
        select = menuInputInt(1, 2);

        switch (select) {
            case 1: 
                secondConfirmation = 1;
                break;

            case 2: 
                exitFlag = 1;
                break;
        }
    }

    while (!overrideFlag && !exitFlag) {
        printf("Enter password to delete account: ");
        
        safeStringScanf(overrideTemp, CONFIG_STRING_LEN);
        encrypt(overrideTemp, config, overrideTemp);

        if (!strcmp("[EXIT]", overrideTemp))
            exitFlag = 1;

        else if (!strcmp(overrideTemp, userData->users[userIndex].password))
            overrideFlag = 1;

        else {
            printf("Password mismatch! Account deletion cancelled.\n");
            exitFlag = 1;
        }
    }

    if (firstConfirmation && secondConfirmation && overrideFlag && !exitFlag) {
        updatePokedexOnDelete(userData, userIndex, sDB);
        deleteAccountFromDB(userData, userIndex);
        returnFlag = 1;
        printf("We're sad to see you go. Thank you for using Chardex!\n");
    }

    return returnFlag;
}

int accountMenu(UserData *userData, int userIndex, Config *config, SDB *sDB) {
    int select = 0, exitFlag = 0, returnFlag = 0;

    while (!returnFlag && !exitFlag) {
        printf("\n");
        printf("=== [ ACCOUNT OPTIONS FOR %s ] ===\n", userData->users[userIndex].username);
        printf("\n");

        printf("[1] Change Password\n");
        printf("[2] Delete Account\n");
        printf("[3] Exit\n");
        printf("\n");

        select = menuInputInt(1, 3);

        switch (select) {
            case 1:
                returnFlag = changePassword(userData, userIndex, config);
                break;

            case 2:
                returnFlag = deleteAccount(userData, userIndex, config, sDB);
                break;

            case 3:
                exitFlag = 1;
                break;
        }
    }

    return returnFlag;
}
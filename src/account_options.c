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

/*

    @name   updatePokedexOnDelete();

    @brief  Helper function to update the species database to decrement species in the user's Pokedex

    @param  *userData   Pointer to the array of users used globally
    @param  userIndex   Index of the current user in the userData->users array
    @param  *sDB        Pointer to the species database used globally

*/
void updatePokedexOnDelete(UserData *userData, int userIndex, SDB *sDB) {
    int searchDB = -1;
    
    // For every species in the user's Pokedex...
    for (int i = 0 ; i < userData->users[userIndex].currentSpeciesCount ; i++) {
        // Get the index of the current species
        searchDB = SpeciesDataBaseSearch(sDB, userData->users[userIndex].species[i].name);
        
        // Decrement
        if (searchDB != 1)
            sDB->species[searchDB].userInputCount--;
    }
}

/*

    @name   deleteAccountFromDB();

    @brief  Helper function to delete the current user from the userData->users array

    @param  *userData   Pointer to the array of users used globally
    @param  userIndex   Index of the current user in the userData->users array

*/
void deleteAccountFromDB(UserData *userData, int userIndex) {
    // Start i at userIndex, replace user in the current i position with the next user
    for (int i = userIndex ; i < userData->currentUserCount ; i++)
        userData->users[i] = userData->users[i + 1];
}

/*

    @name   changePassword();

    @brief  Interaction logic for confirmation of the changing of passwords of the current user

    @param  *userData   Pointer to the array of users used globally
    @param  userIndex   Index of the current user in the userData->users array
    @param  *config     Pointer to the program configuration data

    @return Flag that tells if user should be logged out. (1 if yes, 0 if no) 

*/
int changePassword(UserData *userData, int userIndex, Config *config) {
    char temp[UN_PW_LENGTH] = "", encrypted[UN_PW_LENGTH] = "", encrypted2[UN_PW_LENGTH] = "";
    int oldPWFlag = 0, newPWFlag = 0, exitFlag = 0;

    // Check old password
    while (!oldPWFlag && !exitFlag) {
        printf("Enter old password: ");

        // Get encrypted input
        safeStringScanf(temp, UN_PW_LENGTH);
        encrypt(temp, config, encrypted);

        // Exit if "[EXIT]" is inputted
        if (!strcmp("[EXIT]", temp))
            exitFlag = 1;

        // If encrypted input matches old password
        else if (!strcmp(encrypted, userData->users[userIndex].password))
            oldPWFlag = 1;

        else {
            printf("Password does not match!\n");
        }
        
    }

    if (oldPWFlag && !exitFlag) {

        // Entering new password
        while (!newPWFlag && !exitFlag) {

            printf("Enter Password: ");

            // Get encrypted input
            safeStringScanf(temp, UN_PW_LENGTH);
            encrypt(temp, config, encrypted);

            // Exit if "[EXIT]" is inputted
            if (!strcmp("[EXIT]", temp))
                exitFlag = 1;

            else if (checkIfBanned(temp, UN_PW_LENGTH))
                printf("Invalid Password! (part of banned words list)\n");

            // If PW is less than 3 chars, block
            else if ((int) strlen(temp) < 3)
                printf("Password too short!\n");

            else if (!strcmp(userData->users[userIndex].username, temp))
                printf("Invalid Password! (password cannot be the same as the username)\n");

            else if (!strcmp(userData->users[userIndex].password, encrypted))
                printf("Invalid Password! (password cannot be the same as the old password)\n");

            else {
                printf("Confirm password: ");

                // Get encrypted input
                safeStringScanf(temp, UN_PW_LENGTH);
                encrypt(temp, config, encrypted2);

                // If input matches previous input, update password and userData database file
                if (!strcmp(encrypted2, encrypted)){
                    strcpy(userData->users[userIndex].password, encrypted);
                    setUsers(userData);
                    newPWFlag = 1;
                    printf("Confirmation success!\n");
                    printf("Password change successful! Login again using the new password.\n");
                }

                // Exit if "[EXIT]" is inputted
                else if (!strcmp("[EXIT]", temp))
                    exitFlag = 1;

                else
                    printf("Confirmation mismatch!\n");
            }

        }

    }

    // Return user logout status
    return newPWFlag;
}

/*

    @name   deleteAccount();

    @brief  Interaction logic for confirmation of the deletion of the current user in the userData->users array

    @param  *userData   Pointer to the array of users used globally
    @param  userIndex   Index of the current user in the userData->users array
    @param  *config     Pointer to the program configuration data
    @param  *sDB        Pointer to the species database used globally

    @return Flag that tells if user should be logged out. (1 if yes, 0 if no) 

*/
int deleteAccount(UserData *userData, int userIndex, Config *config, SDB *sDB) {
    char overrideTemp[CONFIG_STRING_LEN] = "";
    int firstConfirmation = 0, secondConfirmation = 0, overrideFlag = 0,
        exitFlag = 0, select = 0, returnFlag = 0;

    // While not first confirmation...
    while (!firstConfirmation && !exitFlag) {

        // Print menu
        printf("Delete account?\n");
        printf("[1] Confirm\n");
        printf("[2] Cancel\n");
        
        // Get input
        select = menuInputInt(1, 2);

        switch (select) {

            // [1] Confirm
            case 1: 
                firstConfirmation = 1;
                break;

            // [2] Cancel
            case 2: 
                exitFlag = 1;
                break;
        
        }

    }

    // While not second confirmation...
    while (!secondConfirmation && !exitFlag) {

        // Print menu
        printf("Last warning! This is irreversible! Confirm?\n");
        printf("[1] Confirm\n");
        printf("[2] Cancel\n");
        
        // Get input
        select = menuInputInt(1, 2);

        switch (select) {

            // [1] Confirm
            case 1: 
                secondConfirmation = 1;
                break;

            // [2] Cancel
            case 2: 
                exitFlag = 1;
                break;

        }

    }

    // Enter own password to finalize confirmation
    while (!overrideFlag && !exitFlag) {
        printf("Enter password to delete account: ");
        
        // Get encrypted password
        safeStringScanf(overrideTemp, CONFIG_STRING_LEN);
        encrypt(overrideTemp, config, overrideTemp);

        // Exit if "[EXIT]" is entered
        if (!strcmp("[EXIT]", overrideTemp))
            exitFlag = 1;

        // If encrypted input matches password... confirm
        else if (!strcmp(overrideTemp, userData->users[userIndex].password))
            overrideFlag = 1;

        // If it does not, cancel account deletion
        else {
            printf("Password mismatch! Account deletion cancelled.\n");
            exitFlag = 1;
        }
    }

    // If all confirmation flags are set, and exitFlag is not marked, delete account
    if (firstConfirmation && secondConfirmation && overrideFlag && !exitFlag) {
        // Update every species in sDB's user count for every species that is in the user's Pokedex
        updatePokedexOnDelete(userData, userIndex, sDB);

        // Shift array by 1
        deleteAccountFromDB(userData, userIndex);
        
        // Log user out
        returnFlag = 1;
        printf("We're sad to see you go. Thank you for using Chardex!\n");
    }

    // Return user logout status
    return returnFlag;
}

/*

    @name   accountMenu();

    @brief  Main Menu for account modification functions, accessed from user_menu.c (both admin and regular user menus)

    @param  *userData   Pointer to the array of users used globally
    @param  userIndex   Index of the current user in the userData->users array
    @param  *config     Pointer to the program configuration data
    @param  *sDB        Pointer to the species database used globally

    @return Flag that tells if user should be logged out. (1 if yes, 0 if no) 

*/
int accountMenu(UserData *userData, int userIndex, Config *config, SDB *sDB) {
    int select = 0, exitFlag = 0, returnFlag = 0;

    // While in menu...
    while (!returnFlag && !exitFlag) {
        // Print Menu
        printf("\n");
        printf("=== [ ACCOUNT OPTIONS FOR %s ] ===\n", userData->users[userIndex].username);
        printf("\n");

        printf("[1] Change Password\n");
        printf("[2] Delete Account\n");
        printf("[3] Exit Menu\n");
        printf("\n");

        // Get Input
        select = menuInputInt(1, 3);

        switch (select) {

            // [1] Change Password
            case 1:
                returnFlag = changePassword(userData, userIndex, config);
                break;

            // [2] Delete Account
            case 2:
                returnFlag = deleteAccount(userData, userIndex, config, sDB);
                break;

            // [3] Exit Menu
            case 3:
                exitFlag = 1;
                break;
        
        }
    
    }

    // Return user logout status
    return returnFlag;
}
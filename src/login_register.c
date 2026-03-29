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
#include "user_menu.h"
#include "species_struct.h"

/*

	@name	loginMenu();

    @brief	Menu for user login

    @param	userData	Pointer to the user database data
    @param	config      Pointer to the configuration data

*/
void loginMenu(UserData *userData, Config *config) {
    // If there are no users, print error
    if (userData->currentUserCount < 1) {
        printf("No users registered!\n");
    }

    else {
        char temp[UN_PW_LENGTH] = "";
        int unFlag = 0, pwFlag = 0, exitFlag = 0, failCounter = 3, index = -1;

        printf("=== [ LOGIN ] ===\n\n");
        printf("Enter \"[EXIT]\" to exit this menu at any time.\n");

        // Get username
        while (!unFlag && !exitFlag) {
            printf("Enter Username: ");

            // Get input from user
            safeStringScanf(temp, UN_PW_LENGTH);
            
            // Search in userDB
            index = UserSearch(userData, temp);

            // Exit if "[EXIT]" is inputted
            if (!strcmp("[EXIT]", temp))
                exitFlag = 1;

            // If UN is found, continue
            else if (index != -1)
                unFlag = 1;

            else
                printf("Username not found!\n");
        }

        // Get password
        while (!pwFlag && !exitFlag) {

            printf("Enter Password: ");

            // Get input from user
            safeStringScanf(temp, UN_PW_LENGTH);

            // Get encrypted
            encrypt(temp, config, temp);

            // Exit if "[EXIT]" is inputted
            if (!strcmp("[EXIT]", temp))
                exitFlag = 1;

            // If encrypted input matches encrypted password
            else if (!strcmp(userData->users[index].password, temp))
                pwFlag = 1;

            // Count login attempts, maximum 3
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

        // Load user menu and species database
        if (unFlag && pwFlag && !exitFlag) {
            printf("Logged in.\n\n");

            // Load Species Database
            SDB sDB;
            getSpecies(&sDB);

            // Admin check
            if (userData->users[index].administrator) {
                adminMenu(userData, index, config, &sDB); 
            }

            else {
                userMenu(userData, index, config, &sDB);
            }
        }

        printf("\n");
    }
    
}

/*

	@name	registerMenu();

    @brief	Menu for user registration

    @param	userData	Pointer to the user database data
    @param	config      Pointer to the configuration data

*/
void registerMenu(UserData *userData, Config *config) {

    // If user database is under user limit
    if (userData->currentUserCount < USER_LIMIT) {
        User user = { 0 };
        char temp[UN_PW_LENGTH] = "", select = '\0';
        int unFlag = 0, pwFlag = 0, exitFlag = 0, adminFlag = 0;

        printf("=== [ REGISTER ] ===\n\n");
        printf("Enter \"[EXIT]\" to exit this menu at any time.\n");

        // Get username
        while (!unFlag && !exitFlag) {

            printf("Enter Username: ");
            safeStringScanf(temp, UN_PW_LENGTH);
            
            // Exit if "[EXIT]" is inputted
            if (!strcmp("[EXIT]", temp))
                exitFlag = 1;

            // If UN contains banned string, block
            else if (checkIfBanned(temp, UN_PW_LENGTH))
                printf("Invalid Username! (part of banned words list)\n");

            // If UN is found in database, block
            else if (UserSearch(userData, temp) != -1)
                printf("User already exists!\n");

            else{
                strcpy(user.username, temp);
                unFlag = 1;
            }

        }

        // Get password
        while (!pwFlag && !exitFlag) {

            printf("Enter Password: ");
            safeStringScanf(temp, UN_PW_LENGTH);

            // Exit if "[EXIT]" is inputted
            if (!strcmp("[EXIT]", temp))
                exitFlag = 1;

            // If PW contains banned string, block
            else if (checkIfBanned(temp, UN_PW_LENGTH))
                printf("Invalid Password! (part of banned words list)\n");

            // If PW == UN, block
            else if (!strcmp(user.username, temp))
                printf("Invalid Password! (password cannot be the same as the username)\n");

            // Confirm password
            else {
                encrypt(temp, config, user.password);
                
                printf("Confirm password: ");
                safeStringScanf(temp, UN_PW_LENGTH);
                
                encrypt(temp, config, temp);

                // If input matches saved
                if (!strcmp(user.password, temp)){
                    pwFlag = 1;
                    printf("Confirmation success!\n");
                }

                // Exit if "[EXIT]" is inputted
                else if (!strcmp("[EXIT]", temp))
                    exitFlag = 1;

                else
                    printf("Confirmation mismatch!\n");
            }

        }

        // Get admin priviliges
        while (!adminFlag && !exitFlag) {
            printf("Register as admin? ([y]es / [N]o): ");
            safeCharScanf(&select);

            // If registering as admin..
            if (select == 'Y' || select == 'y') {
                // Ask for override key
                printf("Enter override key: ");
                safeStringScanf(temp, CONFIG_STRING_LEN);

                // If input matches config, set as admin
                if (!strcmp(temp, config->administratorKey)){
                    user.administrator = 1;
                    printf("Admin priviliges granted.\n");
                    printf("Registering as admin...\n");
                }

                // Else, set as regular user
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

            // Add to user array
            userData->users[userData->currentUserCount] = user;
            userData->currentUserCount++;
            UserSort(userData);
            
            // Save user array
            setUsers(userData);

            printf("Registered! Login to account to use Chardex.\n");
            adminFlag = 1;
            
        }

    }
    
    else {
        printf("Sorry! Maximum amount of users are registered.\n");
    }

    printf("\n");
}

/*

	@name	resetPasswordMenu();

    @brief	Menu for password resetting

    @param	userData	Pointer to the user database data
    @param	config      Pointer to the configuration data

*/
void resetPasswordMenu(UserData *userData, Config *config) {
    // If no users, cancel
    if (userData->currentUserCount < 1) {
        printf("No users registered!\n");
    }

    else {
        char temp[UN_PW_LENGTH] = "", encrypted[UN_PW_LENGTH] = "";
        int unFlag = 0, overrideFlag = 0, pwFlag = 0, exitFlag = 0, index = -1;

        printf("=== [ PASSWORD RESET ] ===\n\n");
        printf("Enter \"[EXIT]\" to exit this menu at any time.\n");

        // Get UN
        while (!unFlag && !exitFlag) {
            printf("Enter Username: ");
            // Get UN from user
            safeStringScanf(temp, UN_PW_LENGTH);

            // Look up UN in user database 
            index = UserSearch(userData, temp);

            // Exit if "[EXIT]" is inputted
            if (!strcmp("[EXIT]", temp))
                exitFlag = 1;

            // If UN is found in database, continue
            else if (index != -1)
                unFlag = 1;

            else
                printf("Username not found!\n");
        }

        // Get override key
        while (!overrideFlag && !exitFlag) {
            printf("Enter override key: ");
            // Get override key from users
            safeStringScanf(temp, CONFIG_STRING_LEN);

            // Exit if "[EXIT]" is inputted
            if (!strcmp("[EXIT]", temp))
                exitFlag = 1;

            // If input matches override key
            else if (!strcmp(temp, config->administratorKey))
                overrideFlag = 1;

            else {
                printf("Invalid override key!\n");
            }
            
        }

        if (unFlag && overrideFlag && !exitFlag) {
            // Get password
            while (!pwFlag && !exitFlag) {

                printf("Enter Password: ");

                // Get new password from user
                safeStringScanf(temp, UN_PW_LENGTH);

                // Encrypt input
                encrypt(temp, config, encrypted);

                // Exit if "[EXIT]" is inputted
                if (!strcmp("[EXIT]", temp))
                    exitFlag = 1;

                // If PW contains banned string, block
                else if (checkIfBanned(temp, UN_PW_LENGTH))
                    printf("Invalid Password! (part of banned words list)\n");

                // If PW == UN, block
                else if (!strcmp(userData->users[index].username, temp))
                    printf("Invalid Password! (password cannot be the same as the username)\n");

                // If new PW == old PW, block
                else if (!strcmp(userData->users[index].password, encrypted))
                    printf("Invalid Password! (password cannot be the same as the old password)\n");

                else {
                    printf("Confirm password: ");
                    
                    // Get confirmation
                    safeStringScanf(temp, UN_PW_LENGTH);

                    // Encrypt confirmation
                    encrypt(temp, config, temp);

                    // If confirmation == previous input
                    if (!strcmp(encrypted, temp)){
                        strcpy(userData->users[index].password, temp);
                        setUsers(userData);
                        pwFlag = 1;
                        printf("Confirmation success!\n");
                        printf("Password reset successful! Login to Chardex using the new password.\n");
                    }

                    // Exit if "[EXIT]" is inputted
                    else if (!strcmp("[EXIT]", temp))
                        exitFlag = 1;

                    else
                        printf("Confirmation mismatch!\n");
                }

            }

        }

    }
}
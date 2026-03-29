/*

    user_menu.c

    Contains the menu for logged in users

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-28-2026

*/

#include <stdio.h>
#include <string.h>

#include "user_struct.h"
#include "species_struct.h"
#include "config_struct.h"
#include "string_helpers.h"
#include "pokedex_menu.h"
#include "species_database_menu.h"
#include "account_options.h"
#include "leaderboard_menu.h"

/*

	@name	userMenu();

    @brief	Main menu for a regular user

    @param  *userData   Pointer to the array of users used globally
    @param  userIndex   Index of the current user in the userData->users array
    @param  *config     Pointer to the program configuration data
    @param  *sDB        Pointer to the species database used globally

*/
void userMenu(UserData *userData, int userIndex, Config *config, SDB *sDB) {
    int exit = 0, select = 0;

    // while not exit...
    while (!exit) {
        printf("=== [ WELCOME %s. ] ===\n\n", userData->users[userIndex].username);
        printf("[1] Own Pokedex\n");
        printf("[2] Species Database\n");
        printf("[3] Leaderboard\n");
        printf("[4] Account Settings\n");
        printf("[5] Logout\n");
        printf("\n");

        // Get user input
        select = menuInputInt(1, 5);

        printf("\n");

        switch (select) {
            // Own Pokedex
            case 1:
                ownPokedexMenu(userData, userIndex, sDB);
                break;

            // Species Database
            case 2:
                speciesDatabaseUserMenu(sDB);
                break;

            // Leaderboard
            case 3:
                leaderboardMenu(userData, sDB);
                break;
            
            // Account Settings
            case 4:
                exit = accountMenu(userData, userIndex, config, sDB);
                break;
            
            // Exit
            case 5:
                exit = 1;
                printf("Thank you for using Chardex!\n");
                break;

        }

    }
}

/*

	@name	adminMenu();

    @brief	Main menu for an administrator

    @param  *userData   Pointer to the array of users used globally
    @param  userIndex   Index of the current user in the userData->users array
    @param  *config     Pointer to the program configuration data
    @param  *sDB        Pointer to the species database used globally

*/
void adminMenu(UserData *userData, int userIndex, Config *config, SDB *sDB) {
    int exit = 0, select = 0;

    // while not exit...
    while (!exit) {
        printf("=== [ WELCOME %s! ] ===\n\n", userData->users[userIndex].username);
        printf("[1] Own Pokedex\n");
        printf("[2] Species Database (admin)\n");
        printf("[3] Leaderboard\n");
        printf("[4] Account Settings\n");
        printf("[5] Logout\n");
        printf("\n");

        // Get input from user
        select = menuInputInt(1, 5);

        printf("\n");
        
        switch (select) {
            // Own Pokedex
            case 1:
                ownPokedexMenu(userData, userIndex, sDB);
                break;

            // Species Database
            case 2:
                speciesDatabaseAdminMenu(sDB);
                break;

            // Leaderboard
            case 3:
                leaderboardMenu(userData, sDB);
                break;
            
            // Account Settings
            case 4:
                exit = accountMenu(userData, userIndex, config, sDB);
                break;
            
            // Exit
            case 5:
                exit = 1;
                printf("Thank you for using Chardex!\n");
                break;

        }

    }
}
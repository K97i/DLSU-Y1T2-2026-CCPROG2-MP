/*

    user_menu.c

    Contains the menu for logged in users

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-28-2026

*/

#include <stdio.h>
#include <string.h>

#include "user_struct.h"
#include "string_helpers.h"

void userMenu(UserData *userData, User *user) {
    int exit = 0, select = 0;

    // while not exit...
    while (!exit) {
        printf("=== [ WELCOME %s. ] ===\n\n", user->username);
        printf("[1] Own Pokedex\n");
        printf("[2] Species Database\n");
        printf("[3] Leaderboard\n");
        printf("[4] Logout\n\n");
        select = menuInputInt(1, 4);

        printf("\n");

        switch (select) {
            // Own Pokedex
            case 1:
                // ownPokedexMenu(userData, user, SDB);
                break;

            // Species Database
            case 2:
                // speciesDatabaseUserMenu(SDB);
                break;

            // Leaderboard
            case 3:
                // leaderboardMenu(userData, SDB);
                break;
            
            // Exit
            case 4:
                exit = 1;
                printf("Thank you for using Chardex!\n");
                break;

        }

    }
}

void adminMenu(UserData *userData, User *user) {
    int exit = 0, select = 0;

    // while not exit...
    while (!exit) {
        printf("=== [ WELCOME %s! ] ===\n\n", user->username);
        printf("[1] Own Pokedex\n");
        printf("[2] Species Database (admin)\n");
        printf("[3] Leaderboard\n");
        printf("[4] Logout\n\n");
        select = menuInputInt(1, 4);

        printf("\n");

        switch (select) {
            // Own Pokedex
            case 1:
                // ownPokedexMenu(userData, user, SDB);
                break;

            // Species Database
            case 2:
                // speciesDatabaseAdminMenu(SDB);
                break;

            // Leaderboard
            case 3:
                // leaderboardMenu(userData, SDB);
                break;
            
            // Exit
            case 4:
                exit = 1;
                printf("Thank you for using Chardex!\n");
                break;

        }

    }
}
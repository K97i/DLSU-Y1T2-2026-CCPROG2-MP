/*

	pokedex_menu.c
	
	Contains the menu for the user's species list
	
	Author: EBORDE, Mikaelo D.
	Last Modified: 3-28-2026

*/

#include <stdio.h>
#include <string.h>

#include "user_struct.h"
#include "species_struct.h"
#include "string_helpers.h"

void ownPokedexMenu(UserData *userData, int userIndex, SDB *sDB) {
    int exit = 0, select = 0;

    // while not exit...
    while (!exit) {
        printf("=== [ POKEDEX ] ===\n\n");
        printf("[1] Display Pokedex\n");
        printf("[2] Edit Pokedex\n");
        printf("[3] Exit Menu\n");
        select = menuInputInt(1, 3);

        printf("\n");

        switch (select) {
            // Own Pokedex
            case 1:
                // displayPokedex(userData, userIndex, sDB);
                break;

            // Species Database
            case 2:
                // editPokedex(userData, user, sDB);
                break;
            
            // Exit
            case 3:
                exit = 1;
                break;

        }

    }
}
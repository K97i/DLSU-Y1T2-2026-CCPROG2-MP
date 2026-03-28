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
#include "search_and_sort.h"
#include "display_helpers.h"

void printPokedex(UserData *userData, int userIndex) {
    printf("=== [ %s's Pokedex ] ===\n\n", userData->users[userIndex].username);

    if (userData->users[userIndex].currentSpeciesCount > 0) {
        for (int i = 0 ; i < userData->users[userIndex].currentSpeciesCount ; i++)
            printSpecies(&userData->users[userIndex].species[i], i);
    }

    else {
        printf("Empty Pokedex! :(\n");
    }

    printf("\n");
}

void searchUserPokedex(UserData *userData, int userIndex, SDB *sDB) {
    char temp[WORD_LIMIT] = "";
    int exit = 0, speciesUserIndex = -1, speciesDatabaseIndex = -1;

    while (!exit) {
        printf("Search own Pokedex for: ");
        safeStringScanf(temp, WORD_LIMIT);

        if (!strcmp("[EXIT]", temp))
            exit = 1;

        else
            speciesUserIndex = SpeciesUserSearch(&userData->users[userIndex], temp);

        if (!exit && speciesUserIndex != -1) {
            printf("Found!\n");

            // Printing Name
            printSpecies(&userData->users[userIndex].species[speciesUserIndex], 0);
            printf("\n");

            // Printing Special Info
            speciesDatabaseIndex = SpeciesDataBaseSearch(sDB, userData->users[userIndex].species[speciesUserIndex].name);
            printSpeciesSpecialInfo(&userData->users[userIndex].species[speciesUserIndex], sDB, speciesDatabaseIndex);

            printf("\n");
        }
    }
}

void editPokedex(UserData *userData, int userIndex, SDB *sDB) {
    int exit = 0, select = 0;

    while (!exit) {
        printPokedex(userData, userIndex);
        printf("[1] Add to Pokedex\n");
        printf("[2] Remove from Pokedex\n");
        printf("[3] Exit Menu\n");
        printf("\n");
        select = menuInputInt(1, 3);

        printf("\n");

        switch (select) {
            // Search Species from Pokedex
            case 1:
                // addToPokedex(userData, userIndex, sDB);
                break;
            
            // Remove from Pokedex
            case 2:
                // removeFromPokedex(userData, userIndex);
                break;
            
            // Exit
            case 3:
                exit = 1;
                break;

        }

    }
}

void displayPokedex(UserData *userData, int userIndex, SDB *sDB) {
    int exit = 0, select = 0;

    while (!exit) {
        printPokedex(userData, userIndex);
        printf("[1] Search Species\n");
        printf("[2] Exit Menu\n");
        printf("\n");
        select = menuInputInt(1, 3);

        printf("\n");

        switch (select) {
            // Search Species from Pokedex
            case 1:
                searchUserPokedex(userData, userIndex, sDB);
                break;
            
            // Exit
            case 2:
                exit = 1;
                break;

        }

    }

}

void ownPokedexMenu(UserData *userData, int userIndex, SDB *sDB) {
    int exit = 0, select = 0;

    // while not exit...
    while (!exit) {
        printf("=== [ POKEDEX ] ===\n\n");
        printf("[1] Display Pokedex\n");
        printf("[2] Edit Pokedex\n");
        printf("[3] Exit Menu\n");
        printf("\n");
        select = menuInputInt(1, 3);

        printf("\n");

        switch (select) {
            // Display Pokedex
            case 1:
                displayPokedex(userData, userIndex, sDB);
                break;

            // Edit Pokedex
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

/*

	species_database_menu.c
	
	Contains the menu for accessing the species database
	
	Author: EBORDE, Mikaelo D.
	Last Modified: 3-28-2026

*/

#include <stdio.h>
#include <string.h>

#include "species_struct.h"
#include "string_helpers.h"
#include "display_helpers.h"
#include "search_and_sort.h"

void searchWholeDatabase(SDB *sDB) {
    char temp[WORD_LIMIT] = "";
    int exit = 0, speciesDatabaseIndex = -1;

    while (!exit) {
        printf("Search own Pokedex for: ");
        safeStringScanf(temp, WORD_LIMIT);

        if (!strcmp("[EXIT]", temp))
            exit = 1;

        else
            speciesDatabaseIndex = SpeciesDataBaseSearch(sDB, temp);

        if (!exit && speciesDatabaseIndex != -1) {
            printf("Found!\n");

            // Printing Name
            printSpeciesData(&sDB->species[speciesDatabaseIndex], 0);
            printf("\n");

            // Printing Special Info
            printSpeciesDatabaseInfo(&sDB->species[speciesDatabaseIndex]);

            printf("\n");
        }
    }
}

void speciesDatabaseUserMenu(SDB *sDB) {
    int exit = 0, select = 0;

    while (!exit) {

        for (int i = 0 ; i < sDB->currentSpeciesCount ; i++) {
            printSpeciesData(&sDB->species[i], i);
        }

        printf("[1] Search Species\n");
        printf("[2] Exit Menu\n");
        printf("\n");
        select = menuInputInt(1, 3);

        printf("\n");

        switch (select) {
            // Search Database
            case 1:
                searchWholeDatabase(sDB);
                break;
            
            // Exit
            case 2:
                exit = 1;
                break;

        }

    }
}

void speciesDatabaseAdminMenu(SDB *sDB) {
    int exit = 0, select = 0;

    while (!exit) {

        for (int i = 0 ; i < sDB->currentSpeciesCount ; i++) {
            printSpeciesData(&sDB->species[i], i);
        }

        printf("[1] Search Species\n");
        printf("[2] Edit Database\n");
        printf("[3] Exit Menu\n");
        printf("\n");
        select = menuInputInt(1, 3);

        printf("\n");

        switch (select) {
            // Search Species from Pokedex
            case 1:
                searchWholeDatabase(sDB);
                break;
            
            // Edit Database
            case 2:
                // editSpeciesDatabase(sDB);
                break;
            
            // Exit
            case 3:
                exit = 1;
                break;

        }

    }
}
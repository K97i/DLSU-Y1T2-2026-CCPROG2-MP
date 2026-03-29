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
#include "edit_species_database.h"

/*

    @name   searchWholeDatabase();

    @brief  Searches the species database if there is a match to the user's input

    @param  *sDB    Pointer to the species database used globally

*/
void searchWholeDatabase(SDB *sDB) {
    char temp[WORD_LIMIT] = "";
    int exit = 0, speciesDatabaseIndex = -1;

    printf("=== [ SEARCH DATABASE ] ===\n");
    printf("\n");
    printf("Enter \"[EXIT]\" to exit this menu at any time.\n");
    printf("\n");

    while (!exit) {
        printf("Search the Database for: ");
        safeStringScanf(temp, WORD_LIMIT); //gets the user's input and clears the input stream

        if (!strcmp("[EXIT]", temp))
            exit = 1;

        else
            speciesDatabaseIndex = SpeciesDataBaseSearch(sDB, temp);

        if (!exit && speciesDatabaseIndex != -1) {
            printf("Found!");
            printf("\n");
            printf("\n");

            printf("=========");
            printf("\n");
            printf("\n");

            // Printing Name
            printSpeciesData(&sDB->species[speciesDatabaseIndex], 0);
            printf("\n");

            // Printing Special Info
            printSpeciesDatabaseInfo(&sDB->species[speciesDatabaseIndex]);

            printf("\n");
            printf("=========");
            printf("\n");
        }

        else if (!exit && speciesDatabaseIndex < 0) {
            printf("Not found! :(\n");
        }
        
        printf("\n");
    }
}

/*

    @name   speciesDatabaseUserMenu();

    @brief  User's view on the menu to display and search the species database

    @param  *sDB    Pointer to the species database used globally

*/
void speciesDatabaseUserMenu(SDB *sDB) {
    int exit = 0, select = 0;

    while (!exit) {

        printf("\n");
        printf("=== [ SPECIES DATABASE ] ===\n");
        printf("\n");

        //prints the entire database
        for (int i = 0 ; i < sDB->currentSpeciesCount ; i++) {
            printSpeciesData(&sDB->species[i], i + 1);
        }

        printf("\n");
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

/*

    @name   speciesDatabaseAdminMenu();

    @brief  Admin's view on the menu to display, search, and edit the database

    @param  *sDB    Pointer to the species database used globally

*/
void speciesDatabaseAdminMenu(SDB *sDB) {
    int exit = 0, select = 0;

    while (!exit) {

        printf("\n");
        printf("=== [ SPECIES DATABASE ] ===\n");
        printf("\n");


        for (int i = 0 ; i < sDB->currentSpeciesCount ; i++) {
            printSpeciesData(&sDB->species[i], i + 1);
        }

        printf("\n");
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
                editSpeciesDatabase(sDB);
                break;
            
            // Exit
            case 3:
                exit = 1;
                break;

        }

        printf("\n");

    }
}
/*

	edit_species_database.c
	
	Contains the menu for editing the species database
	
	Author: EBORDE, Mikaelo D.
	Last Modified: 3-28-2026

*/

#include <stdio.h>
#include <string.h>

#include "species_struct.h"
#include "string_helpers.h"
#include "display_helpers.h"
#include "search_and_sort.h"
#include "file_operation.h"

/*
    MENU
        ADD SPECIES
        EDIT SPECIES
            EDIT CONSERVATION STATUS
            EDIT BIOME
            EDIT DESCRIPTION
*/

void addSpecies(SDB *sDB) {
    SpeciesData newSpecies = { 0 };
    char temp[WORD_LIMIT] = "", tempDescription[DESCRIPTION_LIMIT] = "";
    int exitFlag = 0, databaseIndex = -1, nameFlag = 0, 
        biomeFlag = 0, csFlag = 0, conservationStatus = 2,
        descriptionFlag = 0;

    while (!nameFlag && !exitFlag) {
        printf("Enter name of species: ");
        safeStringScanf(temp, WORD_LIMIT);
        databaseIndex = SpeciesDataBaseSearch(sDB, temp);

        if (!strcmp("[EXIT]", temp))
            exitFlag = 1;

        else if (databaseIndex != -1)
            printf("Species already in database!");

        else if (checkIfBanned(temp, WORD_LIMIT))
            printf("Invalid Name! (part of banned words list)!");

        else {
            strcpy(newSpecies.name, temp);
            nameFlag = 1;            
        }
    }

    while (!biomeFlag && !exitFlag) {
        printf("Enter the biome in which the species is usually found: ");
        safeStringScanf(temp, WORD_LIMIT);

        if (!strcmp("[EXIT]", temp))
            exitFlag = 1;

        else if (checkIfBanned(temp, WORD_LIMIT))
            printf("Invalid Biome! (part of banned words list)!");

        else {
            strcpy(newSpecies.biome, temp);
            biomeFlag = 1;
        }
    }

    while (!csFlag && !exitFlag) {
        printf("Enter the conservation status of the species: ");
        printf("[0] Extinct\n");
        printf("[1] Vulnerable\n");
        printf("[2] Least Concern\n");
        printf("[3] Exit Menu\n");
        
        conservationStatus = menuInputInt(0, 3);

        switch (conservationStatus) {
            case 0:
                newSpecies.conservationStatus = 0;
                break;

            case 1:
                newSpecies.conservationStatus = 1;
                break;

            case 2:
                newSpecies.conservationStatus = 2;
                break;

            case 3:
                exitFlag = 1;
                break;
        }
    }

    while (!descriptionFlag && !exitFlag) {
        printf("Enter the description of the species: ");
        safeStringScanf(tempDescription, DESCRIPTION_LIMIT);

        if (!strcmp("[EXIT]", tempDescription))
            exitFlag = 1;

        else if (checkIfBanned(tempDescription, DESCRIPTION_LIMIT))
            printf("Invalid Description! (part of banned words list)!");

        else {
            strcpy(newSpecies.description, tempDescription);
            descriptionFlag = 1;
        }
    }

    if (nameFlag && biomeFlag && csFlag && descriptionFlag && !exitFlag) {
        sDB->species[sDB->currentSpeciesCount] = newSpecies;
        sDB->currentSpeciesCount++;
        setSpecies(sDB);
    }
}

void editSpeciesDatabase(SDB *sDB) {
    int exit = 0, select = 0;

    // while not exit...
    while (!exit) {
        printf("=== [ EDIT SPECIES DATABASE ] ===\n\n");
        printf("[1] Add Species\n");
        printf("[2] Edit Species\n");
        printf("[3] Exit\n");
        printf("\n");
        select = menuInputInt(1, 3);

        printf("\n");

        switch (select) {
            // Add Species
            case 1:
                // addSpecies(SDB *sDB);
                break;

            // Edit Species
            case 2:
                // editSpecies(userData, config);
                break;

            // Exit
            case 3:
                exit = 1;
                break;

        }

    }
}
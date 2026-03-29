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

void editConservationStatus(SDB *sDB, int speciesIndex) {
    char conservationStatus[WORD_LIMIT] = "";
    int exitFlag = 0, select = 0;

    if (sDB->species[speciesIndex].conservationStatus == 2)
        strcpy(conservationStatus, "Least Concern");

    else if (sDB->species[speciesIndex].conservationStatus == 1)
        strcpy(conservationStatus, "Vulnerable");

    else
        strcpy(conservationStatus, "Exticnt");

    printf("Current conservation status: %s\n", conservationStatus);
    printf("Choices:\n");
    printf("[0] Extinct\n");
    printf("[1] Vulnerable\n");
    printf("[2] Least Concern\n");
    printf("[3] Exit Menu\n");

    printf("Change conservation status to: ");

    select = menuInputInt(0, 3);

    switch (select) {
        case 0:
            sDB->species[speciesIndex].conservationStatus = 0;
            break;

        case 1:
            sDB->species[speciesIndex].conservationStatus = 1;
            break;

        case 2:
            sDB->species[speciesIndex].conservationStatus = 2;
            break;

        case 3:
            exitFlag = 1;
            break;
    }

    if (!exitFlag) {
        setSpecies(sDB);
    }
}

void editBiome(SDB *sDB, int speciesIndex) {
    char temp[WORD_LIMIT] = "";
    int biomeFlag = 0, exitFlag = 0;
    printf("Current Biome: %s", sDB->species[speciesIndex].biome);
    
    while (!biomeFlag && !exitFlag) {
        printf("Enter new biome: ");
        safeStringScanf(temp, WORD_LIMIT);

        if (!strcmp("[EXIT]", temp))
            exitFlag = 1;

        else if (checkIfBanned(temp, WORD_LIMIT))
            printf("Invalid Biome! (part of banned words list)!");

        else {
            strcpy(sDB->species[speciesIndex].biome, temp);
            biomeFlag = 1;
        }
    }

    if (biomeFlag && !exitFlag) {
        setSpecies(sDB);
    }
}

void editDescription(SDB *sDB, int speciesIndex) {
    char tempDescription[DESCRIPTION_LIMIT] = "";
    int descriptionFlag = 0, exitFlag = 0;
    
    printf("Current Description: \n");
    printf("%s\n", sDB->species[speciesIndex].description);

    while (!descriptionFlag && !exitFlag) {
        printf("Enter new description: ");
        safeStringScanf(tempDescription, DESCRIPTION_LIMIT);

        if (!strcmp("[EXIT]", tempDescription))
            exitFlag = 1;

        else if (checkIfBanned(tempDescription, DESCRIPTION_LIMIT))
            printf("Invalid Biome! (part of banned words list)!");

        else {
            strcpy(sDB->species[speciesIndex].description, tempDescription);
            descriptionFlag = 1;
        }
    }

    if (descriptionFlag && !exitFlag) {
        setSpecies(sDB);
    }
}

void editSpeciesSubMenu(SDB *sDB, int speciesIndex) {
    int exit = 0, select = 0; 

    while (!exit) {
        printf("=== [ EDITING %s ] ===\n\n", sDB->species[speciesIndex].name);
        printf("[1] Edit Conservation Status\n");
        printf("[2] Edit Biome\n");
        printf("[3] Edit Description\n");
        printf("[4] Exit Menu\n");

        printf("\n");
        select = menuInputInt(1, 3);

        printf("\n");

        switch (select) {
            // Conservation Status
            case 1:
                editConservationStatus(sDB, speciesIndex);
                break;

            // Biome
            case 2:
                editBiome(sDB, speciesIndex);
                break;

            // Description
            case 3:
                editDescription(sDB, speciesIndex);
                break;

            // Exit
            case 4:
                exit = 1;
                break;

        }

    }
}

void editSpecies(SDB *sDB) {
    char temp[WORD_LIMIT] = "";
    int exitFlag = 0, databaseIndex = -1;

    while (!exitFlag) {
        printf("Enter name of species to edit: ");
        safeStringScanf(temp, WORD_LIMIT);
        databaseIndex = SpeciesDataBaseSearch(sDB, temp);

        if (!strcmp("[EXIT]", temp))
            exitFlag = 1;

        else if (databaseIndex != -1) {
            printf("Found!\n");
            editSpeciesSubMenu(sDB, databaseIndex);
        }

        else
            printf("Species not found!\n");


    }
}

void addSpecies(SDB *sDB) {
    if (sDB->currentSpeciesCount >= SPECIES_LIMIT) {
        printf("Maximum amount of speices reached! Contact developers to increase limit.\n");
    }
    
    else {
        SpeciesData newSpecies = { 0 };
        char temp[WORD_LIMIT] = "", tempDescription[DESCRIPTION_LIMIT] = "";
        int exitFlag = 0, databaseIndex = -1, nameFlag = 0, 
            biomeFlag = 0, csFlag = 0, descriptionFlag = 0, 
            confirmFlag = 0, select = 0;

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
            printf("Enter the conservation status of the species\n");
            printf("[0] Extinct\n");
            printf("[1] Vulnerable\n");
            printf("[2] Least Concern\n");
            printf("[3] Exit Menu\n");
            
            select = menuInputInt(0, 3);

            switch (select) {
                case 0:
                    newSpecies.conservationStatus = 0;
                    csFlag = 1;
                    break;

                case 1:
                    newSpecies.conservationStatus = 1;
                    csFlag = 1;
                    break;

                case 2:
                    newSpecies.conservationStatus = 2;
                    csFlag = 1;
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

        while (!confirmFlag && !exitFlag) {
            printf("Confirm details?");

            printf("\n");
            printf("\n");

            printf("=========");
            printf("\n");
            printf("\n");

            printSpeciesData(&newSpecies, 0);
            
            printf("\n");

            printSpeciesDatabaseInfo(&newSpecies);

            printf("\n");
            printf("=========");
            printf("\n");
            printf("\n");

            printf("\n");
            printf("[1] Confirm\n");
            printf("[2] Cancel\n");
            printf("\n");

            select = menuInputInt(1, 2);

            switch (select) {
                case 1:
                    sDB->species[sDB->currentSpeciesCount] = newSpecies;
                    sDB->currentSpeciesCount++;
                    SpeciesDataBaseSort(sDB);
                    setSpecies(sDB);

                    printf("Added species to database.\n");
                    confirmFlag = 1;
                    break;

                case 2:
                    exitFlag = 1;
                    break;

            }
        }
    }

    printf("\n");
}

void editSpeciesDatabase(SDB *sDB) {
    int exit = 0, select = 0;

    // while not exit...
    while (!exit) {
        printf("=== [ EDIT SPECIES DATABASE ] ===\n\n");
        printf("[1] Add Species\n");
        printf("[2] Edit Species\n");
        printf("[3] Exit Menu\n");
        printf("\n");
        select = menuInputInt(1, 3);

        printf("\n");

        switch (select) {
            // Add Species
            case 1:
                addSpecies(sDB);
                break;

            // Edit Species
            case 2:
                editSpecies(sDB);
                break;

            // Exit
            case 3:
                exit = 1;
                break;

        }

    }
}
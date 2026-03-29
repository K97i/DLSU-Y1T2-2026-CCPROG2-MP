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

	@name	editConservationStatus();

    @brief	Edits the conservation status of the selected species

    @param	sDB	            Pointer of the species array
    @param	speciesIndex	Pointer of the index of the species to edit

*/
void editConservationStatus(SDB *sDB, int speciesIndex) {
    char conservationStatus[WORD_LIMIT] = "";
    int exitFlag = 0, select = 0;

    // Print the current conservation status
    // 2 => Least Concern, 1 => Vulnerable, 0 => Extinct
    if (sDB->species[speciesIndex].conservationStatus == 2)
        strcpy(conservationStatus, "Least Concern");

    else if (sDB->species[speciesIndex].conservationStatus == 1)
        strcpy(conservationStatus, "Vulnerable");

    else
        strcpy(conservationStatus, "Exticnt");

    printf("Current conservation status: %s\n", conservationStatus);

    // Menu Choice
    printf("Choices:\n");
    printf("[0] Extinct\n");
    printf("[1] Vulnerable\n");
    printf("[2] Least Concern\n");
    printf("[3] Exit Menu\n");

    printf("Change conservation status to: ");

    select = menuInputInt(0, 3);

    // Dont save if exit menu
    if (select == 3)
        exitFlag = 1;

    else
        sDB->species[speciesIndex].conservationStatus = select;

    // If not exitflag, save database
    if (!exitFlag) {
        setSpecies(sDB);
    }
}

/*

	@name	editBiome();

    @brief	Edits the biome of the selected species

    @param	sDB	            Pointer of the species array
    @param	speciesIndex	Pointer of the index of the species to edit

*/
void editBiome(SDB *sDB, int speciesIndex) {
    char temp[WORD_LIMIT] = "";
    int biomeFlag = 0, exitFlag = 0;

    // Print current biome
    printf("Current Biome: %s", sDB->species[speciesIndex].biome);
    
    // While not valid biome...
    while (!biomeFlag && !exitFlag) {
        // Get new biome from user
        printf("Enter new biome: ");
        safeStringScanf(temp, WORD_LIMIT);

        // Exit if "[EXIT]" is inputted
        if (!strcmp("[EXIT]", temp))
            exitFlag = 1;

        // If in banned word list, block
        else if (checkIfBanned(temp, WORD_LIMIT))
            printf("Invalid Biome! (part of banned words list)!");

        // Update DB if valid
        else {
            strcpy(sDB->species[speciesIndex].biome, temp);
            biomeFlag = 1;
        }
    }

    if (biomeFlag && !exitFlag) {
        // Save DB if valid
        setSpecies(sDB);
    }
}

/*

	@name	editDescription();

    @brief	Edits the Description of the selected species

    @param	sDB	            Pointer of the species array
    @param	speciesIndex	Pointer of the index of the species to edit

*/
void editDescription(SDB *sDB, int speciesIndex) {
    char tempDescription[DESCRIPTION_LIMIT] = "";
    int descriptionFlag = 0, exitFlag = 0;
    
    // Print current description
    printf("Current Description: \n");
    printf("%s\n", sDB->species[speciesIndex].description);

    // While not valid description...
    while (!descriptionFlag && !exitFlag) {
        // Get new description from user
        printf("Enter new description: ");
        safeStringScanf(tempDescription, DESCRIPTION_LIMIT);

        // Exit if "[EXIT]" is inputted
        if (!strcmp("[EXIT]", tempDescription))
            exitFlag = 1;

        // If in banned word list, block
        else if (checkIfBanned(tempDescription, DESCRIPTION_LIMIT))
            printf("Invalid Biome! (part of banned words list)!");

        // Update DB if valid
        else {
            strcpy(sDB->species[speciesIndex].description, tempDescription);
            descriptionFlag = 1;
        }
    }

    // Save DB if valid description
    if (descriptionFlag && !exitFlag) {
        setSpecies(sDB);
    }
}

/*

	@name	editSpeciesSubMenu();

    @brief	Holds options to edit specified species

    @param	sDB	            Pointer of the species array
    @param	speciesIndex	Pointer of the index of the species to edit

*/
void editSpeciesSubMenu(SDB *sDB, int speciesIndex) {
    int exit = 0, select = 0; 

    while (!exit) {
        // Menu choices
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

/*

	@name	editSpecies();

    @brief	Selects species to edit

    @param	sDB     Pointer of the species array

*/
void editSpecies(SDB *sDB) {
    char temp[WORD_LIMIT] = "";
    int exitFlag = 0, databaseIndex = -1;

    while (!exitFlag) {
        // Get species from user 
        printf("Enter name of species to edit: ");
        safeStringScanf(temp, WORD_LIMIT);
        
        // Search for index
        databaseIndex = SpeciesDataBaseSearch(sDB, temp);

        // Exit if "[EXIT]" is inputted
        if (!strcmp("[EXIT]", temp))
            exitFlag = 1;
            
        // If found in database, move to submenu with species index
        else if (databaseIndex != -1) {
            printf("Found!\n");
            editSpeciesSubMenu(sDB, databaseIndex);
        }

        else
            printf("Species not found!\n");


    }
}

/*

	@name	addSpecies();

    @brief	Adds a new species to the species array

    @param	sDB     Pointer of the species array

*/
void addSpecies(SDB *sDB) {
    // Checks if array is full
    if (sDB->currentSpeciesCount >= SPECIES_LIMIT) {
        printf("Maximum amount of speices reached! Contact developers to increase limit.\n");
    }
    
    // If array is NOT full...
    else {
        // Data holder for input
        SpeciesData newSpecies = { 0 };
        char temp[WORD_LIMIT] = "", tempDescription[DESCRIPTION_LIMIT] = "";
        int exitFlag = 0, databaseIndex = -1, nameFlag = 0, 
            biomeFlag = 0, csFlag = 0, descriptionFlag = 0, 
            confirmFlag = 0, select = 0;

        // Gets name
        while (!nameFlag && !exitFlag) {
            printf("Enter name of species: ");
            safeStringScanf(temp, WORD_LIMIT);
            databaseIndex = SpeciesDataBaseSearch(sDB, temp);

            if (!strcmp("[EXIT]", temp))
                exitFlag = 1;

            // Checks if species is already in database
            else if (databaseIndex != -1)
                printf("Species already in database!");

            // Checks if it contains banned words
            else if (checkIfBanned(temp, WORD_LIMIT))
                printf("Invalid Name! (part of banned words list)!");

            else {
                strcpy(newSpecies.name, temp);
                nameFlag = 1;            
            }
        }

        // Gets biome
        while (!biomeFlag && !exitFlag) {
            printf("Enter the biome in which the species is usually found: ");
            safeStringScanf(temp, WORD_LIMIT);

            if (!strcmp("[EXIT]", temp))
                exitFlag = 1;

            // Checks if it contains banned words
            else if (checkIfBanned(temp, WORD_LIMIT))
                printf("Invalid Biome! (part of banned words list)!");

            else {
                strcpy(newSpecies.biome, temp);
                biomeFlag = 1;
            }
        }

        // Gets conservation status
        while (!csFlag && !exitFlag) {
            printf("Enter the conservation status of the species\n");
            printf("[0] Extinct\n");
            printf("[1] Vulnerable\n");
            printf("[2] Least Concern\n");
            printf("[3] Exit Menu\n");
            
            select = menuInputInt(0, 3);

            switch (select) {
                // Extinct
                case 0:
                    newSpecies.conservationStatus = 0;
                    csFlag = 1;
                    break;

                // Vulnerable
                case 1:
                    newSpecies.conservationStatus = 1;
                    csFlag = 1;
                    break;

                // Least Concern
                case 2:
                    newSpecies.conservationStatus = 2;
                    csFlag = 1;
                    break;

                // Exit Menu
                case 3:
                    exitFlag = 1;
                    break;
            }
        }

        // Gets description
        while (!descriptionFlag && !exitFlag) {
            printf("Enter the description of the species: ");
            safeStringScanf(tempDescription, DESCRIPTION_LIMIT);

            if (!strcmp("[EXIT]", tempDescription))
                exitFlag = 1;

            // Checks if it contains banned words
            else if (checkIfBanned(tempDescription, DESCRIPTION_LIMIT))
                printf("Invalid Description! (part of banned words list)!");

            else {
                strcpy(newSpecies.description, tempDescription);
                descriptionFlag = 1;
            }
        }

        // Get confirmation of data from user
        while (!confirmFlag && !exitFlag) {
            // Print all new info
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
                    // Update species database
                    sDB->species[sDB->currentSpeciesCount] = newSpecies;
                    sDB->currentSpeciesCount++;
                    SpeciesDataBaseSort(sDB);

                    // Save species database
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

/*

	@name	editSpeciesDatabase();

    @brief	Main menu for options to edit the species array

    @param	sDB     Pointer of the species array

*/
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
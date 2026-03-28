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
                // removeFromPokedex(userData, userIndex, sDB);
                break;
            
            // Exit
            case 3:
                exit = 1;
                break;

        }

    }
}

void addToPokedex(UserData *userData, int userIndex, SDB *sDB) {
    char species[WORD_LIMIT] = { 0 };
    int sex = 0, age = 0, select = 0, i = userData->users[userIndex].currentSpeciesCount;
    float height = 0.0, weight = 0.0;

    printf("Enter the species you want to add: ");
    safeCharScanf(species);

    int index = SpeciesDataBaseSearch(sDB, species); //searches the Species Database if it's in the list
    int flag = SpeciesUserSearch(&userData->users[userIndex], species); //searches the pokedex of the user

    if(index != -1 && flag == -1) { //checks if the species exist in the database and the user doesn't have it yet in their pokedex
        printf("Input the Height of the Species: ");
        scanf("%f", height);
        printf("Input the Weight of the Species: ");
        scanf("%f", weight);
        printf("Input the Age of the Species: ");
        scanf("%d", age);
        printf("Input the Sex of the Species (1-male, 2-female, and 0-undefined): ");
        scanf("%d", sex);

        printf("\nConfirm Addtion?\n");
        printf("[1] yes\n");
        printf("[2] no\n");
        select = menuInputInt(1,2);

        printf("\n");

        switch(select) {
            // Add the data into the user's pokedex
            case 1:
                strcpy(userData->users[userIndex].species[i-1].name, species);
                userData->users[userIndex].species[i-1].height = height;
                userData->users[userIndex].species[i-1].weight = weight;
                userData->users[userIndex].species[i-1].age = age;
                userData->users[userIndex].species[i-1].sex = sex;
                userData->users->currentSpeciesCount++;
                break;
            
            // Cancels
            case 2:
                printf("Addition successfully canceled\n");
                break;
        }
    }
    else
        printf("Not a valid species\n");
}

void removeFromPokedex(UserData *userData, int userIndex) {
    char species[WORD_LIMIT] = { 0 };
    int select = 0;

    printf("Enter the species you want to remove: ");
    safeCharScanf(species);

    int index = SpeciesUserSearch(&userData->users[userIndex], species); //searches the User's Database if it's in the list

    if(index != -1) {
        printf("\nConfirm Removal?\n");
        printf("[1] yes\n");
        printf("[2] no\n");
        select = menuInputInt(1,2);

        printf("\n");

        switch(select) {
            //Remove the data in the user's pokedex
            case 1:
                strcpy(userData->users[userIndex].species[index].name, "");
                userData->users[userIndex].species[index].height = 0.0;
                userData->users[userIndex].species[index].weight = 0.0;
                userData->users[userIndex].species[index].age = 0;
                userData->users[userIndex].species[index].sex = 0;

                //shifts the pokedex entries 
                for(int i = index; i < userData->users[userIndex].currentSpeciesCount - 1; i++) {
                    userData->users[userIndex].species[i] = userData->users[userIndex].species[i++];
                }
                userData->users->currentSpeciesCount--;
                break;
            
            //Cancels
            case 2:
                printf("Removal successfully canceled\n");
                break;
        }
    }
    else
        printf("This species is not in your pokedex\n");

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

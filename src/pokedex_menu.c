/*

	pokedex_menu.c
	
	Contains the menu for the user's species list
	
	Author: EBORDE, Mikaelo D., SACRAMENTO, Yvan Gregorio A.
	Last Modified: 3-29-2026

*/

#include <stdio.h>
#include <string.h>

#include "user_struct.h"
#include "species_struct.h"
#include "string_helpers.h"
#include "search_and_sort.h"
#include "display_helpers.h"
#include "file_operation.h"

/*

    @name   printPokedex();

    @brief  Prints the user's Pokedex

    @param  *userData   Pointer to the array of users used globally
    @param  userIndex   Index of the current user in the userData->users array

*/
void printPokedex(UserData *userData, int userIndex) {
    printf("=== [ %s's Pokedex ] ===\n\n", userData->users[userIndex].username);

    if (userData->users[userIndex].currentSpeciesCount > 0) {
        for (int i = 0 ; i < userData->users[userIndex].currentSpeciesCount ; i++)
            printSpecies(&userData->users[userIndex].species[i], i + 1);
    }

    else {
        printf("Empty Pokedex! :(\n");
    }

    printf("\n");
}

/*

    @name   searchUserPokedex();

    @brief  Searches species within the user's pokedex

    @param  *userData   Pointer to the array of users used globally
    @param  userIndex   Index of the current user in the userData->users array
    @param  *sDB        Pointer to the species database 

*/
void searchUserPokedex(UserData *userData, int userIndex, SDB *sDB) {
    char temp[WORD_LIMIT] = "";
    int exit = 0, speciesUserIndex = -1, speciesDatabaseIndex = -1;

    printf("Enter \"[EXIT]\" to exit this menu at any time.\n");

    if (userData->users[userIndex].currentSpeciesCount > 0) {
        while (!exit) {
            printf("Search own Pokedex for: ");
            safeStringScanf(temp, WORD_LIMIT); //gets the user's input and clears the input stream

            if (!strcmp("[EXIT]", temp))
                exit = 1;

            else
                speciesUserIndex = SpeciesUserSearch(&userData->users[userIndex], temp);

            if (!exit && speciesUserIndex != -1) {
                printf("Found!\n");

                printf("=========");
                printf("\n");
                printf("\n");

                // Printing Name
                printSpecies(&userData->users[userIndex].species[speciesUserIndex], 0);
                printf("\n");

                // Printing Special Info
                speciesDatabaseIndex = SpeciesDataBaseSearch(sDB, userData->users[userIndex].species[speciesUserIndex].name);
                printSpeciesSpecialInfo(&userData->users[userIndex].species[speciesUserIndex], sDB, speciesDatabaseIndex);

                printf("\n");
                printf("=========");
                printf("\n");
                printf("\n");
            }

            else if (!exit && speciesUserIndex < 0) {
                printf("Not found! :(\n");
                printf("\n");
            }
        }
    }

    else {
        printf("Empty Pokedex! :(\n");
        printf("\n");
    }
}

/*

    @name   addToPokedex();

    @brief  Menu for adding species in a given user's pokedex

    @param  *userData   Pointer to the array of users used globally
    @param  userIndex   Index of the current user in the userData->users array
    @param  *sDB        Pointer to the species database 

*/
void addToPokedex(UserData *userData, int userIndex, SDB *sDB) {
    Species new = { 0 };
    char temp[WORD_LIMIT] = { 0 };
    int tempInt = 0, tempDB = -1, tempUser = -1, select = 0, exitFlag = 0, nameFlag = 0, 
        heightFlag = 0, weightFlag = 0, ageFlag = 0, sexFlag = 0;
    float tempFloat = 0.0;

    /*
        HEIGHT - safeFloat
        WEIGHT - safeFloat
        AGE - safeInt
        SEX - menuInt
    */

    while (!nameFlag && !exitFlag) {
        printf("Enter the species you want to add: ");
        safeStringScanf(temp, WORD_LIMIT); //gets the user's input and clears the input stream

        tempDB = SpeciesDataBaseSearch(sDB, temp); //searches the Species Database if it's in the list
        tempUser = SpeciesUserSearch(&userData->users[userIndex], temp); //searches the pokedex of the user

        if (!strcmp("[EXIT]", temp))
            exitFlag = 1;

        //checks if the species exist in the database and the user doesn't have it yet in their pokedex
        else if(tempDB != -1 && tempUser <= -1) {
            nameFlag = 1;
            strcpy(new.name, temp);
        }

        else if (tempDB <= -1)
            printf("Not found in species database!\n");

        else if (tempUser != -1)
            printf("Species already in Pokedex!\n");
    }

    while (!heightFlag && !exitFlag) {
        printf("Enter the height of the species: ");
        safeFloatScanf(&tempFloat); //gets the user's input and clears the input stream


        if (tempFloat < 0) //checks if the height is valid
            printf("Invalid height! (height can't be negative!)\n");

        else {
            new.height = tempFloat;
            heightFlag = 1;
        }
    }

    while (!weightFlag && !exitFlag) { 
        printf("Enter the weight of the species: ");
        safeFloatScanf(&tempFloat); //gets the user's input and clears the input stream


        if (tempFloat < 0) //checks if the weight is valid
            printf("Invalid weight! (weight can't be negative!)\n");

        else {
            new.weight = tempFloat;
            weightFlag = 1;
        }
    }

    while (!ageFlag && !exitFlag) {
        printf("Enter the age of the species: ");
        safeIntScanf(&tempInt); //gets the user's input and clears the input stream

        if (tempInt < 0) //checks if the age is valid
            printf("Invalid age! (age can't be negative!)\n");

        else {
            new.age = tempInt;
            ageFlag = 1;
        }
    }

    while (!sexFlag && !exitFlag) {
        printf("Select the sex of the species\n");
        printf("\n");
        printf("Choices:\n");
        printf("[0] Undefined\n");
        printf("[1] Male\n");
        printf("[2] Female\n");
        printf("[3] Exit Menu\n");

        select = menuInputInt(0, 3);

        if (select == 3)
            exitFlag = 1;

        else {
            new.sex = select;
            sexFlag = 1;
        }
    }
    
    if (!exitFlag) {

        if (new.sex == 0)
            strcpy(temp, "Undefined");

        else
            new.sex % 2 ? strcpy(temp, "Male") : strcpy(temp, "Female"); //set the new.sex to corresponding string


        printf("Confirm addition?\n");
        printf("\n");

        printf("%s\n", new.name);
        printf("\n");
        printf("Height: %0.1f\n", new.height);
        printf("Weight: %0.1f\n", new.weight);
        printf("Age: %d\n", new.age);
        printf("Sex: %s\n", temp);
        printf("\n");

        printf("[1] Confirm\n");
        printf("[2] Cancel\n");

        select = menuInputInt(1, 2);

        switch (select) {
            //Confirmed: adds the new species into the user's pokedex
            case 1:
                userData->users[userIndex].species[userData->users[userIndex].currentSpeciesCount] = new;
                userData->users[userIndex].currentSpeciesCount++;
                setUsers(userData);

                // Update species index
                sDB->species[tempDB].userInputCount++;
                setSpecies(sDB);

                printf("Confirmed! Congratulations on your new specimen!\n");
                break;

            case 2:
                printf("Addition cancelled.\n");
                exitFlag = 1;
                break;
                
        }
    }

    printf("\n");
}

/*

    @name   removeFromPokedex();

    @brief  Menu for removing species in a given user's pokedex

    @param  *userData   Pointer to the array of users used globally
    @param  userIndex   Index of the current user in the userData->users array
    @param  *sDB        Pointer to the species database 

*/
void removeFromPokedex(UserData *userData, int userIndex, SDB *sDB) {
    char temp[WORD_LIMIT] = { 0 };
    int searchIndex = -1, dbIndex = -1, select = 0, exitFlag = 0, nameFlag = 0, confirmFlag = 0;

    while (!nameFlag && !exitFlag) { //continues looping until either a valid species input or user exits

        printf("Enter the species you want to remove: ");
        safeStringScanf(temp, WORD_LIMIT); //gets the user's input and clears the input stream

        searchIndex = SpeciesUserSearch(&userData->users[userIndex], temp); //searches the User's Database if it's in the list

        if (!strcmp("[EXIT]", temp))
            exitFlag = 1;

        else if (searchIndex != -1) //checks if the species is in the user's pokedex
            nameFlag = 1;
            
        else
            printf("This species is not in your pokedex\n");

    }

    while (!confirmFlag && !exitFlag) {
        printf("Confirm Removal of %s?\n", userData->users[userIndex].species[searchIndex].name);
        printf("\n");
        printf("[1] Confirm\n");
        printf("[2] Cancel\n");
        printf("\n");

        select = menuInputInt(1,2);

        printf("\n");

        switch(select) {
            //Remove the data in the user's pokedex
            case 1:
                //shifts the pokedex entries 
                for(int i = searchIndex; i < userData->users[userIndex].currentSpeciesCount; i++) {
                    userData->users[userIndex].species[i] = userData->users[userIndex].species[i + 1];
                }
                userData->users[userIndex].currentSpeciesCount--;
                setUsers(userData);

                // Update species index
                dbIndex = SpeciesDataBaseSearch(sDB, temp);
                if (dbIndex != -1){
                    sDB->species[dbIndex].userInputCount--;
                    setSpecies(sDB);
                }

                printf("Removed specimen from Pokedex.\n");
                confirmFlag = 1;
                break;
            
            //Cancels
            case 2:
                printf("Removal canceled\n");
                exitFlag = 1;
                break;
        }
    }

    printf("\n");

}

/*

    @name   editPokedex();

    @brief  Main Menu for adding and removing species from the user's pokedex

    @param  *userData   Pointer to the array of users used globally
    @param  userIndex   Index of the current user in the userData->users array
    @param  *sDB        Pointer to the species database 

*/
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
                addToPokedex(userData, userIndex, sDB);
                break;
            
            // Remove from Pokedex
            case 2:
                removeFromPokedex(userData, userIndex, sDB);
                break;
            
            // Exit
            case 3:
                exit = 1;
                break;

        }

    }

}

/*

    @name   displayPokedex();

    @brief  Menu for displaying the user's pokedex and searching in it

    @param  *userData   Pointer to the array of users used globally
    @param  userIndex   Index of the current user in the userData->users array
    @param  *sDB        Pointer to the species database 

*/
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

/*

    @name   displayPokedex();

    @brief  Main Menu for the user's pokedex
    
    @param  *userData   Pointer to the array of users used globally
    @param  userIndex   Index of the current user in the userData->users array
    @param  *sDB        Pointer to the species database 

*/
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
                editPokedex(userData, userIndex, sDB);
                break;
            
            // Exit
            case 3:
                exit = 1;
                break;

        }

    }
}

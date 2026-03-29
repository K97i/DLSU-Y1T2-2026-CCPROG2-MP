/*

	leaderboard.c
	
	Contains the menu for the leaderboard for both user and species
	
	Author: SACRAMENTO, Yvan Gregorio A.
	Last Modified: 3-28-2026
*/

#include <stdio.h>
#include <string.h>

#include "user_struct.h"
#include "species_struct.h"
#include "search_and_sort.h"
#include "string_helpers.h"

/*

		@name	searchSpeciesLeaderboard();

    @brief	Searches for input in the sorted species database

    @param	database	Pointer of the sorted species array

*/
void searchSpeciesLeaderboard(SDB *database) {
	char species[WORD_LIMIT] = { 0 };
	int exitFlag = 0, searchFlag = 0, searchIndex = -1;

	// Title
	printf("=== [ SEARCH SPECIES ] ===\n");
	printf("\n");
	printf("Enter \"[EXIT]\" to exit this menu at any time.\n");
	printf("\n");

	while (!exitFlag) {
		// Get input from user
		printf("\n");
		printf("Enter the Name of the Species: ");

		//accepts the user's species input
		safeStringScanf(species, WORD_LIMIT);
		printf("\n");

		// Exit if "[EXIT]" is inputted
		if (!strcmp("[EXIT]", species))
			exitFlag = 1;

		// Else, check database
		else {

			// Manual linear search, as it is sorted by count instead of name
			for (int i = 0 ; i < database->currentSpeciesCount && !searchFlag ; i++) {
				if (!strcmp(database->species[i].name, species)) {
					searchIndex = i;
					searchFlag = 1;
				}
			}

			// If in database, print
			if (searchIndex != -1) {
				printf("Found!\n");
				printf("\n");

				printf("Ranked #%d: %s (%d users)\n", searchIndex + 1,
												database->species[searchIndex].name,
												database->species[searchIndex].userInputCount);

			}

			else {
				printf("Not found in leaderboard!\n");
			}

			printf("\n");


		}

	}

}

/*

		@name	searchUserLeaderboard();

    @brief	Searches for input in the sorted userdata array

    @param	database	Pointer of the sorted userdata array

*/
void searchUserLeaderboard(UserData *database) {
	char username[UN_PW_LENGTH] = { 0 };
	int exitFlag = 0, searchFlag = 0, searchIndex = -1;

	// Title
	printf("=== [ SEARCH USERNAME ] ===\n");
	printf("\n");
	printf("Enter \"[EXIT]\" to exit this menu at any time.\n");
	printf("\n");
	
	while (!exitFlag) {
		// Get input
		printf("Enter the Name of the User: ");

		//accepts the user's username input
		safeStringScanf(username, UN_PW_LENGTH);
		printf("\n");

		// Exit if "[EXIT]" is inputted
		if (!strcmp("[EXIT]", username))
			exitFlag = 1;

		// Else, check in database
		else {

			// Manual linear search, as it is sorted by count instead of name
			for (int i = 0 ; i < database->currentUserCount && !searchFlag ; i++) {
				if (!strcmp(database->users[i].username, username)) {
					searchIndex = i;
					searchFlag = 1;
				}
			}

			// If found, print
			if (searchIndex != -1) {
				
				printf("Found!\n");

				printf("Ranked #%d: %s (%d species added, latest: %s)\n", searchIndex + 1,
																		database->users[searchIndex].username, 
																		database->users[searchIndex].currentSpeciesCount, 
																		database->users[searchIndex].species[database->users[searchIndex].currentSpeciesCount-1].name);
			}

			else
				printf("Not found in index!\n");
		}

		printf("\n");

	}
}

/*

		@name	sortUserLeaderboard();

    @brief	Sorts the database by currentSpeciesCount

    @param	database	Pointer of the unsorted userdata array

    @return	The sorted array

*/
UserData sortUserLeaderboard(UserData *database) {
	UserData new = *database;

	//Sorts the database by species count in descending order
	for(int i = 0; i < new.currentUserCount - 1; i++) {
		int first = i;
		
		//loops through the rest of the array
		for(int j = i + 1; j < new.currentUserCount; j++) {
			if(new.users[first].currentSpeciesCount < new.users[j].currentSpeciesCount)
				first = j;
		}
		//swaps the structs
		if(first != i) {
			User temp = new.users[i];
			new.users[i] = new.users[first];
			new.users[first] = temp;
		}
	}

	return new;
}

/*

		@name	sortUserLeaderboard();

    @brief	Sorts the database by userInputCount

    @param	database	Pointer of the unsorted species array

    @return	The sorted array

*/
SDB sortSpeciesDatabase(SDB *database) {

	SDB new = *database;

	//Sorts the database by user count in descending order
	for(int i = 0; i < new.currentSpeciesCount - 1; i++) {
		int first = i;
		
		//loops through the rest of the array
		for(int j = i + 1; j < new.currentSpeciesCount; j++) {
			if(new.species[first].userInputCount < new.species[j].userInputCount)
				first = j;
		}
		//swapping the structs
		if(first != i) {
			SpeciesData temp = new.species[i];
			new.species[i] = new.species[first];
			new.species[first] = temp;
		}
	}

	return new;
}

/* 
		
		@name	UserLeaderboard();

    @brief  Menu for displaying the user leaderboard based on the who has the highest species count, average species per user, and search user feature

    @param  database	Copy of the array of users used globally
*/
void UserLeaderboard(UserData *database) {
	int exit = 0, select = 0;
	float sum = 0.0, averageSpU = 0.0;

	UserData sorted = sortUserLeaderboard(database);

	//Solves for the average of species per user
	for(int k = 0; k < sorted.currentUserCount; k++) {
		sum += sorted.users[k].currentSpeciesCount;
	}
	averageSpU = sum / sorted.currentUserCount;

	// While not exit...
	while(!exit) {

		printf("=== [ USER LEADERBOARD ] ===\n");
		printf("\n");

		//Displays Top 10
		for(int r = 0; r < 10 && r < sorted.currentUserCount && sorted.users[r].currentSpeciesCount > 0; r++) {
			printf("%d. %s (%d species added, latest: %s)\n", r + 1, 
									sorted.users[r].username, 
									sorted.users[r].currentSpeciesCount, 
									sorted.users[r].species[sorted.users[r].currentSpeciesCount-1].name);
		}

		printf("\n");
		printf("Average Species per User: %.2f\n", averageSpU);
		printf("\n");

		printf("[1] Search Username\n");
    	printf("[2] Exit Menu\n");
		printf("\n");

		//accepts the user's input (1-2)
		select = menuInputInt(1, 2);
		
		printf("\n");

		switch (select) {
				// Search Username
				case 1:
					searchUserLeaderboard(&sorted);
					break;
				
				// Exit Menu
				case 2:
					exit = 1;
					break;
			}
	}
}

/* 
		
		@name		SpeciesLeaderboard();

    @brief	Menu for displaying the species leaderboard based on the who has the highest user count and search species feature

    @param	database   Copy of the species database used globally
*/
void SpeciesLeaderboard(SDB *database) {
	int exit = 0, select = 0;
	float sum = 0.0, averageUpS;

	SDB sorted = sortSpeciesDatabase(database);

	//Solves for the average of species per user
	for(int k = 0; k < sorted.currentSpeciesCount; k++) {
		sum += sorted.species[k].userInputCount;
	}
	averageUpS = sum / sorted.currentSpeciesCount;
	
	while(!exit) {
		printf("=== [ SPECIES LEADERBOARD ] ===\n");
		printf("\n");
		for(int r = 0; r < 10 && r < sorted.currentSpeciesCount && sorted.species[r].userInputCount > 0; r++) {
			printf("%d. %s (%d users)\n", r + 1, 
									sorted.species[r].name,
									sorted.species[r].userInputCount);
		}

		printf("\n");
		printf("Average Species per User: %.2f\n", averageUpS);
		printf("\n");

		printf("[1] Search Species\n");
    	printf("[2] Exit Menu\n");
		select = menuInputInt(1, 2); //accepts the user's input (1-2)
		
		printf("\n");

    switch (select) {
			// Search Species
			case 1:
				searchSpeciesLeaderboard(&sorted);
				break;
			
			// Exit Menu
			case 2:
				exit = 1;
				break;
		}
	}
}

/* 
		
		@name		leaderboardMenu();

    @brief	Main Menu for displaying the user and species leaderboard

    @param	*userData   Pointer to the array of users used globally
		@param	*speciesDataBase Pointer to the species database used globally
*/
void leaderboardMenu(UserData *userData, SDB *speciesDataBase) {
	int exit = 0, select = 0;

    // while not exit...
  while (!exit) {
	// Title and option
    printf("=== [ LEADERBOARD ] ===\n");
	printf("\n");
    printf("[1] User Leaderboard\n");
    printf("[2] Species Leaderboard\n");
	printf("[3] Exit Menu\n");
	printf("\n");

	//accepts the user's input (1-3)
	select = menuInputInt(1, 3); 

	printf("\n");

    switch (select) {
			// User Leaderboard
			case 1: 
				UserLeaderboard(userData);
				break;

			// Species Leaderboard
			case 2:
				SpeciesLeaderboard(speciesDataBase);
				break;

			// Exit
			case 3:
				exit = 1;
				break;
		}
	}
}


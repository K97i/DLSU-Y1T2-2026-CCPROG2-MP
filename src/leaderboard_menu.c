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
	Function prints the Leaderboard Menu
*/
void leaderboardMenu(UserData userData, SDB speciesDataBase) {
	int exit = 0, select = 0;

    // while not exit...
  while (!exit) {
    printf(" [ LEADERBOARD ] \n");
    printf("[1] User Leaderboard\n");
    printf("[2] Species Leaderboard\n");
		printf("[3] Exit\n");
		select = menuInputInt(1, 3); //accepts the user's input (1-3)

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
		}
	}
}

/*
	Function prints the User Leaderboard Menu
*/
void UserLeaderboard(UserData database) {
	int exit = 0, select = 0, sum = 0;
	float averageSpU = 0.0;

	//Sorts the database by species count in descending order
	for(int i = 0; i < database.currentUserCount - 1; i++) {
		int first = i;
		
		//loops through the rest of the array
		for(int j = i + 1; j < database.currentUserCount; j++) {
			if(database.users[first].currentSpeciesCount < database.users[j].currentSpeciesCount)
				first = j;
		}
		//swaps the structs
		if(first != i) {
			User temp = database.users[i];
			database.users[i] = database.users[first];
			database.users[first] = temp;
		}
	}

	//Solves for the average of species per user
	for(int k = 0; k < database.currentUserCount; k++) {
		sum += database.users[k].currentSpeciesCount;
	}
	averageSpU = sum / database.currentUserCount;


	printf(" [ USER LEADERBOARD ] \n");
	//Displays Top 10
	for(int r = 1; r <= 10 && r <= database.currentUserCount; r++) {
		printf("%d. %s %d %s\n", r, 
														database.users[r-1].username, 
														database.users[r-1].administrator, 
														database.users[r-1].species[database.users[r-1].currentSpeciesCount-1].name);
	}
	while(!exit) {
		printf("[1] Search Username\n");
    printf("[2] Exit Menu\n");
		select = menuInputInt(1, 2); //accepts the user's input (1-2)
		
		printf("\n Average Species per User: %.2f\n", averageSpU);
		printf("\n");

    switch (select) {
			// Search Username
			case 1:
				char username[UN_PW_LENGTH] = { 0 };

				printf(" [ SEARCH USERNAME ] ");
				printf("Enter the Name of the User: ");
				safeCharScanf(username); //accepts the user's username input
				int index = UserSearch(&database, username); // searches the user in the User Database
				printf("%s %d %s\n", 
														database.users[index].username, 
														database.users[index].administrator, 
														database.users[index].species[database.users[index].currentSpeciesCount-1].name);
				break;
			
			// Exit Menu
			case 2:
				exit = 1;
		}
	}
}

/*
	Function prints the Species Leaderboard Menu
*/
void SpeciesLeaderboard(SDB database) {
	int exit = 0, select = 0;

	//Sorts the database by user count in descending order
  for(int i = 0; i < database.currentSpeciesCount - 1; i++) {
		int first = i;
		
		//loops through the rest of the array
		for(int j = i + 1; j < database.currentSpeciesCount; j++) {
			if(database.species[first].userInputCount < database.species[j].userInputCount)
				first = j;
		}
		//swapping the structs
		if(first != i) {
			SpeciesData temp = database.species[i];
			database.species[i] = database.species[first];
			database.species[first] = temp;
		}
  }

	printf(" [ SPECIES LEADERBOARD ]");
	for(int r = 1; r <= 10; r++) {
		printf("%d. %s %d\n", r, 
													database.species[r-1].name,
													database.species[r-1].userInputCount);
	}
	while(!exit) {
		printf("[1] Search Species\n");
    printf("[2] Exit Menu\n");
		select = menuInputInt(1, 2); //accepts the user's input (1-2)
		
		printf("\n");

    switch (select) {
			// Search Species
			case 1:
				char species[WORD_LIMIT] = { 0 };
				printf(" [ SEARCH SPECIES ] ");
				printf("Enter the Name of the Species: ");
				safeCharScanf(species); //accepts the user's species input
				int index = SpeciesDataBaseSearch(&database, species);  // searches the species in the Species Database
				printf("%s %d\n",
												database.species[index].name,
												database.species[index].userInputCount);
				break;
			
			// Exit Menu
			case 2:
					exit = 1;
		}
	}
}
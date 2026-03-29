/*

	search_and_sort.c
	
	Functions that will perform the searching and sorting algorithms for the different databases
	
	Author: SACRAMENTO, Yvan Gregorio A.
	Last Modified: 3-28-2026
*/

#include <stdio.h>
#include <string.h>

#include "user_struct.h"
#include "species_struct.h"


/*

    @name   UserSearch();

    @brief  Searches the user data array if there is a match to the given username (uses binary search)

    @param  *userData   Pointer to the array of users used globally (constant)
    @param  *username		String of the username that is being searched in the *userData

    @return	flag gives the index where the user is located in the array

*/
int UserSearch(const UserData *userData, char *username) {
	int start = 0, end = userData->currentUserCount - 1, flag = -1;
	
	while(flag == -1 && start <= end) {
		int mid = start + (end - start) / 2;
		
		if(strcmp(userData->users[mid].username, username) == 0) { //assigns the index to flag
			flag = mid;
		}
		else if(strcmp(userData->users[mid].username, username) < 0) { //searches upper half
			start = mid + 1;
		}
		else if(strcmp(userData->users[mid].username, username) > 0) { //searches lower half
			end = mid - 1;
		}
	}
	
	return flag; //index
}

/*

    @name   SpeciesDataBaseSearch();

    @brief  Searches the species database if there is a match to the given species (uses binary search)

    @param  *database   Pointer to the species database used globally (constant)
    @param  *species		String of the species that is being searched in the *database

    @return	flag gives the index where the species is located in the database

*/
int SpeciesDataBaseSearch(const SDB *database, char *species) {
	int start = 0, end = database->currentSpeciesCount - 1, flag = -1;
	
	while(flag == -1 && start <= end) {
		int mid = start + (end - start) / 2;
		
		if(strcmp(database->species[mid].name, species) == 0) { //assigns the index to flag
			flag = mid;
		}
		else if(strcmp(database->species[mid].name, species) < 0) { //searches upper half
			start = mid + 1;
		}
		else if(strcmp(database->species[mid].name, species) > 0) { //searches lower half
			end = mid - 1;
		}
	}
	
	return flag; //index
}

/*

    @name   UserSort();

    @brief  Sorts the array of users (uses selection sort)

    @param	*database Pointer to the array of users used globally

*/
void UserSort(UserData *database) {
	
	for(int i = 0; i < database->currentUserCount - 1; i++) {
		int first = i;
		
		//loops through the rest of the array
		for(int j = i + 1; j < database->currentUserCount; j++) {
			if(strcmp(database->users[first].username, database->users[j].username) > 0)
				first = j;
		}
		//swapping the structs
		if(first != i) {
			User temp = database->users[i];
			database->users[i] = database->users[first];
			database->users[first] = temp;
		}
	}
}

/*

    @name   SpeciesDataBaseSort();

    @brief  Sorts the species (uses selection sort)

    @param	*database Pointer to the species database used globally

*/
void SpeciesDataBaseSort(SDB *database) {
	
	for(int i = 0; i < database->currentSpeciesCount - 1; i++) {
		int first = i;
		
		//loops through the rest of the array
		for(int j = i + 1; j < database->currentSpeciesCount; j++) {
			if(strcmp(database->species[first].name, database->species[j].name) > 0)
				first = j;
		}
		//swapping the structs
		if(first != i) {
			SpeciesData temp = database->species[i];
			database->species[i] = database->species[first];
			database->species[first] = temp;
		}
	}
}

/*

    @name   SpeciesUserSearch();

    @brief  Searches the user's array of species if there is a match to the given species (uses linear search)

    @param  *data			Pointer to a user's data (constant)
    @param  *species		String of the species that is being searched in the species array

    @return	flag gives the index where the species is located in the database

*/
int SpeciesUserSearch(const User *data, char *species) {
	int flag = -1;
	
	for(int i = 0; i < data->currentSpeciesCount; i++) {
		if(strcmp(data->species[i].name, species) == 0)
			flag = i; // assigns the index to flag
	}

	return flag; //index
}

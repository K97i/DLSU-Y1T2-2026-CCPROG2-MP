/*

	search_and_sort.c
	
	Functions that will perform the searching and sorting algorithms for the different databases
	
	Author: SACRAMENTO, Yvan Gregorio A.
	Last Modified: 3-26-2026
*/

#include <stdio.h>
#include <string.h>

#include "user_struct.h"
#include "species_struct.h"
/*
	Uses binary search
	param target stores the searched user
	returns flag to determine if found
	to update to UserData
*/
int UserSearch(UserData *userData, char *username, User *target) {
	int start = 0, end = userData->currentUserCount - 1, flag = 0;

	// if only one user
	if (userData->currentUserCount - 1 == 0 && !strcmp(userData->users[0].username, username)) {
		*target = userData->users[0];
		flag = 1;
	} 
	
	else {
		while(flag != 1 && start <= end) {
			int mid = (start + end) / 2;

			if(strcmp(userData->users[mid].username, username) == 0) {
				*target = userData->users[mid];
				flag = 1;
			}
			else if(strcmp(userData->users[mid].username, username) < 0) { //searches upper half
				start = mid + 1;
			}
			else if(strcmp(userData->users[mid].username, username) > 0) { //searches lower half
				end = mid - 1;
			}
		}
	}
	
	
	
	return flag;
}

/*
	Uses binary search
	param target stores the searched species
	returns flag to determine if found
	to update to SpeciesData
*/
int SpeciesSearch(Species database[], int speciesCount, char *species, Species *target) {
	int start = 0, end = speciesCount - 1, flag = 0;
	
	while(flag != 1 && start <= end) {
		int mid = (start + end) / 2;
		
		if(strcmp(database[mid].name, species) == 0) {
			*target = database[mid];
			flag = 1;
		}
		else if(strcmp(database[mid].name, species) < 0) { //searches upper half
			start = mid + 1;
		}
		else if(strcmp(database[mid].name, species) > 0) { //searches lower half
			end = mid - 1;
		}
	}
	
	return flag;
}

/*
	Uses selection sort
	to update to UserData
*/
void UserSort(UserData *database) {
	
	for(int i = 0; i < database->currentUserCount - 2; i++) {
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
	Uses selection sort
	to update to SpeciesData
*/
void SpeciesSort(Species database[], int speciesCount) {
	
	for(int i = 0; i < speciesCount - 2; i++) {
		int first = i;
		
		//loops through the rest of the array
		for(int j = i + 1; j < speciesCount; j++) {
			if(strcmp(database[first].name, database[j].name) > 0)
				first = j;
		}
		//swapping the structs
		if(first != i) {
			Species temp = database[i];
			database[i] = database[first];
			database[first] = temp;
		}
	}

}

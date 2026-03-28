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
int UserSearch(const UserData *userData, char *username) {
	int start = 0, end = userData->currentUserCount - 1, flag = -1;
	
	while(flag == -1 && start <= end) {
		int mid = (start + end) / 2;
		
		if(strcmp(userData->users[mid].username, username) == 0) {
			flag = mid;
		}
		else if(strcmp(userData->users[mid].username, username) < 0) { //searches upper half
			start = mid + 1;
		}
		else if(strcmp(userData->users[mid].username, username) > 0) { //searches lower half
			end = mid - 1;
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
int SpeciesDataBaseSearch(const SDB *database, char *species) {
	int start = 0, end = database->currentSpeciesCount - 1, flag = -1;
	
	while(flag == -1 && start <= end) {
		int mid = (start + end) / 2;
		
		if(strcmp(database->species[mid].name, species) == 0) {
			flag = mid;
		}
		else if(strcmp(database->species[mid].name, species) < 0) { //searches upper half
			start = mid + 1;
		}
		else if(strcmp(database->species[mid].name, species) > 0) { //searches lower half
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
void SpeciesSort(SDB *database) {
	
	for(int i = 0; i < database->currentSpeciesCount - 2; i++) {
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

int SpeciesUserSearch(const User *data, char *species) {
	int start = 0, end = data->currentSpeciesCount - 1, flag = -1;
	
	while(flag == -1 && start <= end) {
		int mid = (start + end) / 2;
		
		if(strcmp(data->species[mid].name, species) == 0) {
			flag = mid;
		}
		else if(strcmp(data->species[mid].name, species) < 0) { //searches upper half
			start = mid + 1;
		}
		else if(strcmp(data->species[mid].name, species) > 0) { //searches lower half
			end = mid - 1;
		}
	}
	
	return flag;
}

void SpeciesUserSort(User *data) {

	for(int i = 0; i < data->currentSpeciesCount - 2; i++) {
		int first = i;
		
		//loops through the rest of the array
		for(int j = i + 1; j < data->currentSpeciesCount; j++) {
			if(strcmp(data->species[first].name, data->species[j].name) > 0)
				first = j;
		}
		//swapping the structs
		if(first != i) {
			Species temp = data->species[i];
			data->species[i] = data->species[first];
			data->species[first] = temp;
		}
	}
}

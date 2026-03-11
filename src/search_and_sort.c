/*

	search_and_sort.c
	
	Functions that will perform the searching and sorting algorithms for the different databases
	
	Author: SACRAMENTO, Yvan Gregorio A.
	Last Modified: 3-10-2026
*/

#include <stdio.h>
#include <string.h>

#include <user_struct.h>
#include <species_struct.h>
/*
	Uses binary search
	param target stores the searched user
	returns flag to determine if found
*/
int UserSearch(User database[], int userCount, char *username, User *target) {
	int start = 0, end = userCount - 1, flag = 0;
	
	while(flag != 1 && start < end) {
		int mid = (start + end) / 2;
		
		if(strcmp(database[mid].username, username) == 0) {
			target = database[mid];
			flag = 1;
		}
		else if(strcmp(database[mid].username, username) < 0) { //searches upper half
			start = mid + 1;
		}
		else if(strcmp(database[mid].username, username) > 0) { //searches lower half
			end = mid - 1;
		}
	}
	
	return flag;
}

/*
	Uses binary search
	param target stores the searched species
	returns flag to determine if found
*/
int SpeciesSearchSearch(Species database[], int speciesCount, char *species, Species *target) {
	int start = 0, end = speciesCount - 1, flag = 0;
	
	while(flag != 1 && start < end) {
		int mid = (start + end) / 2;
		
		if(strcmp(database[mid].name, species) == 0) {
			target = database[mid];
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
*/
void UserSort(User database[], int userCount) {
	
	for(int i = 0; i < userCount - 2; i++) {
		int first = i;
		
		//loops through the rest of the array
		for(int j = i + 1; j < userCount; j++) {
			if(strcmp(database[first].username, datebase[j].username) > 0)
				first = j;
		}
		//swapping the structs
		if(first != i) {
			User temp = database[i];
			database[i] = database[first];
			database[first] = temp;
		}
	}
}

/*
	Uses selection sort
*/
void SpeciesSort(Species database[], int speciesCount) {
	
	for(int i = 0; i < speciesCount - 2; i++) {
		int first = i;
		
		//loops through the rest of the array
		for(int j = i + 1; j < speciesCount; j++) {
			if(strcmp(database[first].name, datebase[j].names) > 0)
				first = j;
		}
		//swapping the structs
		if(first != i) {
			User temp = database[i];
			database[i] = database[first];
			database[first] = temp;
		}
	}

}

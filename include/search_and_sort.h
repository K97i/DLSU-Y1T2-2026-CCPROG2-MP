/*

	search_and_sort.h
	
	Header file for search_and_sort.c
	
	Author: EBORDE, Mikaelo D.
	Last Modified: 3-26-2026

*/

#ifndef SEARCH_AND_SORT
#define SEARCH_AND_SORT

#include "user_struct.h"
#include "species_struct.h"

int UserSearch(const UserData *userData, char *username, User *target);
int SpeciesSearch(Species database[], int speciesCount, char *species, Species *target);
void UserSort(UserData *database);
void SpeciesSort(Species database[], int speciesCount);

#endif
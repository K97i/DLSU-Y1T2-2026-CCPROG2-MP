/*

	search_and_sort.h
	
	Header file for search_and_sort.c
	
	Author: EBORDE, Mikaelo D.
	Last Modified: 3-28-2026

*/

#ifndef SEARCH_AND_SORT
#define SEARCH_AND_SORT

#include "user_struct.h"
#include "species_struct.h"

int UserSearch(const UserData *userData, char *username);
int SpeciesDataBaseSearch(const SDB *database, char *species);
void UserSort(UserData *database);
void SpeciesDataBaseSort(SDB *database);
int SpeciesUserSearch(const User *data, char *species);

#endif
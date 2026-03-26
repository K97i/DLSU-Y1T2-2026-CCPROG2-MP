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

int UserSearch(User database[], int userCount, char *username, User *target);
int SpeciesSearchSearch(Species database[], int speciesCount, char *species, Species *target);
void UserSort(User database[], int userCount);
void SpeciesSort(Species database[], int speciesCount);

#endif
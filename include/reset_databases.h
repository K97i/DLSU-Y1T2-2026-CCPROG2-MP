/*

	reset_databases.h
	
	Header file for reset_databases.c
	
	Author: EBORDE, Mikaelo D.
	Last Modified: 3-28-2026

*/

#ifndef RESET_DATABASES
#define RESET_DATABASES

#include "config_struct.h"

void resetConfig();
void resetDatabases(UserData *userData, Config *config);

#endif
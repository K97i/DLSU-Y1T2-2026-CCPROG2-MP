/*

	leaderboard.c
	
	Functions that will print the leaderboard for both user and species
	
	Author: SACRAMENTO, Yvan Gregorio A.
	Last Modified: 3-28-2026
*/

#include <stdio.h>
#include <string.h>

#include "user_struct.h"
#include "species_struct.h"


void UserLeaderboard(UserData database) {
	
	for(int i = 0; i < database.currentUserCount - 2; i++) {
		int first = i;
		
		//loops through the rest of the array
		for(int j = i + 1; j < database.currentUserCount; j++) {
			if(database.users[first].currentSpeciesCount < database.users[j].currentSpeciesCount)
				first = j;
		}
		//swapping the structs
		if(first != i) {
			User temp = database.users[i];
			database.users[i] = database.users[first];
			database.users[first] = temp;
		}
	}

  for(int r = 1; r <= 10; r++) {
    printf("%d. %s %d %s", r, 
                            database.users[r-1].username, 
                            database.users[r-1].administrator, 
                            database.users[r-1].species[database.users[r-1].currentSpeciesCount]);
  }
}

void SpeciesLeaderboard(SDB database) {

  for(int i = 0; i < database.currentSpeciesCount - 2; i++) {
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

	for(int r = 1; r <= 10; r++) {
		printf("%d. %s %d", r, 
													database.species[r-1].name,
													database.species[r-1].userInputCount);
	}
}
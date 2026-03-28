/*

	display_helpers.c
	
	Contains helper functions to help with printing species
	
	Author: EBORDE, Mikaelo D.
	Last Modified: 3-28-2026

*/

#include <stdio.h>
#include <string.h>

#include "user_struct.h"
#include "species_struct.h"
#include "string_helpers.h"

void printSpecies(Species *species, int numbered, int customNumber) {
    if (numbered)
        printf("%d: ", numbered);

    printf("%s", species->name);
}

void printSpeciesInfo(Species *species, SDB *sDB, int databaseIndex) {
    // CALCULATION 1
    char sex[WORD_LIMIT] = "";
    float bodyMassIndex = species->weight * (species->height * species->height);

    if (species->sex == 0)
        strcpy(sex, "Undefined");

    else
        species->sex % 2 ? strcpy(sex, "Male") : strcpy(sex, "Female");

    

    if (databaseIndex != -1) {
        printf("%s\n\n", sDB->species[databaseIndex].description);
        printf("Biome: %s\n", sDB->species[databaseIndex].biome);
    }

    printf("Sex: %s\n", sex);
    printf("Age: %d\n", species->age);
    printf("Weight: %0.1f kg\n", species->weight);
    printf("Height: %0.1f cm\n", species->height);
    printf("BMI: %0.1f\n", bodyMassIndex);
}

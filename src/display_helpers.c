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

void printSpecies(Species *species, int numbered) {
    if (numbered)
        printf("%d: ", numbered);

    printf("%s\n", species->name);
}

void printSpeciesData(SpeciesData *species, int numbered) {
    if (numbered)
        printf("%d: ", numbered);

    printf("%s\n", species->name);
}

void printSpeciesDatabaseInfo(SpeciesData *species) {
    char conservationStatus[WORD_LIMIT] = "";
    
    if (species->conservationStatus == 2)
        strcpy(conservationStatus, "Least Concern");

    else if (species->conservationStatus == 1)
        strcpy(conservationStatus, "Vulnerable");

    else
        strcpy(conservationStatus, "Exticnt");

    printf("%s\n\n", species->description);
    printf("Conservation Status: %s\n", conservationStatus);
    printf("Biome: %s\n", species->biome);
}

void printSpeciesSpecialInfo(Species *species, SDB *sDB, int databaseIndex) {
    // CALCULATION 1
    char sex[WORD_LIMIT] = "";
    float bodyMassIndex = species->weight * (species->height * species->height);

    if (species->sex == 0)
        strcpy(sex, "Undefined");

    else
        species->sex % 2 ? strcpy(sex, "Male") : strcpy(sex, "Female");

    if (databaseIndex != -1)
        printSpeciesDatabaseInfo(&sDB->species[databaseIndex]);

    printf("Sex: %s\n", sex);
    printf("Age: %d\n", species->age);
    printf("Weight: %0.1f kg\n", species->weight);
    printf("Height: %0.1f cm\n", species->height);
    printf("BMI: %0.1f\n", bodyMassIndex);
}
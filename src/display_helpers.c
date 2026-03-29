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

/*

	@name	printSpecies();

    @brief	Basic print of the specimen name

    @param	species     Pointer of the species data
    @param	numbered	Pointer of the index of the species to edit

*/
void printSpecies(Species *species, int numbered) {
    // If number != 0, print the number
    if (numbered)
        printf("%d: ", numbered);

    printf("%s\n", species->name);
}

/*

	@name	printSpecies();

    @brief	Basic print of the specimen name, but for SpeciesData

    @param	species     Pointer of the species data
    @param	numbered	Pointer of the index of the species to edit

*/
void printSpeciesData(SpeciesData *species, int numbered) {
    // If number != 0, print the number
    if (numbered)
        printf("%d: ", numbered);

    printf("%s\n", species->name);
}

/*

	@name	printSpeciesDatabaseInfo();

    @brief	Prints the metadata from the species database

    @param	species     Pointer of the species data

*/
void printSpeciesDatabaseInfo(SpeciesData *species) {
    char conservationStatus[WORD_LIMIT] = "";
    
    // Set proper conservation status in words
    // 2 => Least Concern, 1 => Vulnerable, 0 => Extinct
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

/*

	@name	printSpeciesSpecialInfo();

    @brief	Prints all available metadata for the specimen

    @param	species     Pointer of the species data
    @param	species     Pointer of the species array
    @param	species     Index of the species in the species array 

*/
void printSpeciesSpecialInfo(Species *species, SDB *sDB, int databaseIndex) {
    // CALCULATION 1
    char sex[WORD_LIMIT] = "";
    float bodyMassIndex = species->weight * (species->height * species->height);

    // Get the sex of the specimen
    if (species->sex == 0)
        strcpy(sex, "Undefined");

    else
        species->sex % 2 ? strcpy(sex, "Male") : strcpy(sex, "Female");

    // If databaseIndex is set, print the metadata from the database 
    if (databaseIndex != -1)
        printSpeciesDatabaseInfo(&sDB->species[databaseIndex]);

    printf("\n");
    printf("Sex: %s\n", sex);
    printf("Age: %d\n", species->age);
    printf("Weight: %0.1f kg\n", species->weight);
    printf("Height: %0.1f cm\n", species->height);
    printf("BMI: %0.1f\n", bodyMassIndex);
}